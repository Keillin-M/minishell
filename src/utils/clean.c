/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:40:25 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/12 14:20:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"
#include "cmd.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	ft_clean(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (cmd)
	{
		if (cmd->in_fd >= 0)
			close(cmd->in_fd);
		if (cmd->out_fd >= 0)
			close(cmd->out_fd);
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->path)
			free(cmd->path);
		free_cmd_lst(cmd);
	}
	if (shell)
	{
		if (shell->paths)
			free_array(shell->paths);
		if (shell->env_list)
			ft_lstclear(&shell->env_list, free_env);
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_all_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	close_fd(&cmd->in_fd);
	close_fd(&cmd->out_fd);
	close_fd(&cmd->fd[0]);
	close_fd(&cmd->fd[1]);
	close_fd(&cmd->prev_fd);
}
