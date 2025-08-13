/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:54:16 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 15:24:16 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	execute_command(t_cmd *cmd, t_shell *shell, char **envp)
{
	int	exit_code;

	if (is_builtin(cmd->cmd))
	{
		exit_code = execute_builtin(cmd->args, shell);
		if (exit_code == -42)
			exit(get_last_exit_status());
		exit(exit_code);
	}
	if (!cmd->path)
		handle_exec_error(cmd->cmd);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		if (errno == ENOENT && (cmd->cmd[0] == '/' 
				|| ft_strncmp(cmd->cmd, "./", 2) == 0))
			print_command_error(cmd->cmd, 1);
		else
			print_command_error(cmd->cmd, 0);
		exit(127);
	}
}

int	init_files(t_cmd *cmd, t_shell *shell)
{
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	if (init_input_files(cmd, shell) != 0)
		return (1);
	if (init_output_files(cmd) != 0)
		return (1);
	return (0);
}

static void	child(t_cmd *cmd, t_shell *shell, char **envp)
{
	if (cmd->here_doc && cmd->in_fd != -1)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (cmd->infile && cmd->in_fd != -1)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (cmd->outfile && cmd->out_fd != -1)
		dup2(cmd->out_fd, STDOUT_FILENO);
	if (cmd->in_fd != -1)
		close(cmd->in_fd);
	if (cmd->out_fd != -1)
		close(cmd->out_fd);
	execute_command(cmd, shell, envp);
}

void	handle_single_builtin(t_cmd *cmd_list, t_shell *shell, char **envp)
{
	int	exit_code;

	if (cmd_list->infile || cmd_list->outfile || cmd_list->here_doc)
		exec_cmd(cmd_list, shell, envp);
	else
	{
		exit_code = execute_builtin(cmd_list->args, shell);
		if (exit_code == -42)
		{
			shell->should_exit = 1;
			shell->exit_status = get_last_exit_status();
		}
		else
			set_last_exit_status(exit_code);
	}
}

void	exec_cmd(t_cmd *cmd, t_shell *shell, char **envp)
{
	pid_t	pid;
	int		status;

	if (init_files(cmd, shell))
	{
		set_last_exit_status(1);
		return ;
	}
	pid = fork();
	if (pid == -1)
		error_exit(shell, cmd, "fork failed\n");
	if (pid == 0)
	{
		setup_child_signals();
		child(cmd, shell, envp);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
		handle_signal_exit(status);
	else if (WIFEXITED(status))
		set_last_exit_status(WEXITSTATUS(status));
	else
		set_last_exit_status(1);
}
