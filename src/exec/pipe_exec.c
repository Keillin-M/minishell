/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:24:39 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 15:30:05 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_child(t_cmd *cmd, t_shell *shell, char **envp)
{
	if (cmd->prev_fd != -1)
		close(cmd->prev_fd);
	close(cmd->fd[0]);
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	setup_child_signals();
	execute_command(cmd, shell, envp);
}

static void	last_child(t_cmd *cmd, t_shell *shell, char **envp)
{
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	if (cmd->fd[1] != -1)
		close(cmd->fd[1]);
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	else
	{
		dup2(cmd->prev_fd, STDIN_FILENO);
	}
	close(cmd->prev_fd);
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	setup_child_signals();
	execute_command(cmd, shell, envp);
}

static void	middle_child(t_cmd *cmd, int i, t_shell *shell, char **envp)
{
	(void)i;
	if (cmd->fd[0] != -1)
		close(cmd->fd[0]);
	dup2(cmd->prev_fd, STDIN_FILENO);
	close(cmd->prev_fd);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	setup_child_signals();
	execute_command(cmd, shell, envp);
}

void	pipex(t_pipe_info *info)
{
	if (info->cmd->next && pipe(info->cmd->fd) == -1)
		error_exit(NULL, info->cmd, "pipe failed\n");
	info->pid[info->i] = fork();
	if (info->pid[info->i] == -1)
		error_exit(NULL, info->cmd, "fork failed\n");
	if (info->pid[info->i] == 0)
	{
		if (info->i == 0)
			first_child(info->cmd, info->shell, info->envp);
		else if (!info->cmd->next)
			last_child(info->cmd, info->shell, info->envp);
		else
			middle_child(info->cmd, info->i, info->shell, info->envp);
	}
	if (info->cmd->prev_fd != -1)
		close(info->cmd->prev_fd);
	if (info->cmd->next)
	{
		close(info->cmd->fd[1]);
		info->cmd->next->prev_fd = info->cmd->fd[0];
	}
}

void	exec_pipe(t_cmd *cmd_list, int cmd_count, t_shell *shell, char **envp)
{
	t_pipe_info	info;
	pid_t		*pid;
	t_cmd		*cmd;

	cmd = cmd_list;
	cmd->prev_fd = -1;
	pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pid)
		error_exit(NULL, cmd_list, "malloc failed\n");
	init_pipe_info(&info, pid, shell, envp);
	while (cmd)
	{
		setup_pipe_execution(&info, cmd, shell);
		cmd = cmd->next;
	}
	cmd = cmd_list;
	while (cmd)
	{
		close_all_fds(cmd);
		cmd = cmd->next;
	}
	wait_for_pipes(pid, cmd_count);
	free(pid);
}
