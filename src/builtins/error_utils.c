/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:00:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/14 11:47:22 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_invalid_identifier_error(char *command, char *identifier)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	print_command_error(char *cmd, int error_type)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (error_type == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

void	handle_exec_error(char *cmd, t_shell *shell)
{
	t_env	*path_env;

	path_env = find_env_var(shell->env_list, "PATH");
	if (ft_strchr(cmd, '/') || !path_env)
		print_command_error(cmd, 1);
	else
		print_command_error(cmd, 0);
	exit(127);
}

void	print_file_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
