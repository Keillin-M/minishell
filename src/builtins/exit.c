/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:20:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/12 14:20:20 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_exit(char **args)
{
	int		exit_status;
	char	*endptr;

	exit_status = 0;
	printf("exit\n");
	if (args[1])
	{
		exit_status = (int)strtol(args[1], &endptr, 10);
		if (*endptr != '\0' || args[1][0] == '\0')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit_status = 2;
		}
		else if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	set_last_exit_status(exit_status & 255);
	return (-42);
}

static int	*get_exit_status_ptr(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	set_last_exit_status(int status)
{
	int	*exit_status_ptr;

	exit_status_ptr = get_exit_status_ptr();
	*exit_status_ptr = status;
}

int	get_last_exit_status(void)
{
	int	*exit_status_ptr;

	exit_status_ptr = get_exit_status_ptr();
	return (*exit_status_ptr);
}

void	error_exit(t_shell *shell, t_cmd *cmd, char *msg)
{
	perror(msg);
	ft_clean(cmd, shell);
	exit(1);
}
