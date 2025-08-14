/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:45:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/14 10:52:32 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_info(t_pipe_info *info, pid_t *pid, t_shell *shell, 
			char **envp)
{
	info->i = 0;
	info->pid = pid;
	info->shell = shell;
	info->envp = envp;
}

void	handle_pipe_signal_exit(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		set_last_exit_status(130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		set_last_exit_status(131);
	}
	else
		set_last_exit_status(128 + WTERMSIG(status));
}

void	handle_signal_exit(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		set_last_exit_status(130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		set_last_exit_status(131);
	}
	else
		set_last_exit_status(128 + WTERMSIG(status));
}

void	setup_pipe_execution(t_pipe_info *info, t_cmd *cmd, t_shell *shell)
{
	if (init_files(cmd, shell))
	{
		close_all_fds(cmd);
		free(info->pid);
		set_last_exit_status(1);
		return ;
	}
	info->cmd = cmd;
	if (pipex(info))
	{
		close_all_fds(cmd);
		free(info->pid);
		set_last_exit_status(1);
		return ;
	}
	info->i++;
}

void	wait_for_pipes(pid_t *pid, int cmd_count)
{
	int	i;
	int	status;

	signal(SIGINT, SIG_IGN);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFSIGNALED(status))
				handle_pipe_signal_exit(status);
			else if (WIFEXITED(status))
				set_last_exit_status(WEXITSTATUS(status));
			else
				set_last_exit_status(1);
		}
		i++;
	}
	setup_signals();
}
