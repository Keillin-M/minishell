/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthajan <tthajan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:20:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/11 15:57:52 by tthajan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_parent_dir(char *current_path)
{
	char	*last_slash;
	char	*parent_path;

	last_slash = ft_strrchr(current_path, '/');
	if (last_slash && last_slash != current_path)
	{
		parent_path = ft_substr(current_path, 0, last_slash - current_path);
		return (parent_path);
	}
	else
		return (ft_strdup("/"));
}

static char	*get_logical_path(char *path, t_shell *shell)
{
	t_env	*pwd_env;

	if (path[0] == '/')
		return (ft_strdup(path));
	else if (ft_strncmp(path, "..", 2) == 0 && path[2] == '\0')
	{
		pwd_env = find_env_var(shell->env_list, "PWD");
		if (pwd_env && pwd_env->value)
			return (get_parent_dir(pwd_env->value));
		else
			return (getcwd(NULL, 0));
	}
	else
		return (getcwd(NULL, 0));
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*pwd;
	char	*new_logical_path;

	pwd = getenv("PWD");
	if (pwd)
		pwd = ft_strdup(pwd);
	path = get_cd_path(args);
	if (!path)
	{
		free(pwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(pwd);
		return (1);
	}
	new_logical_path = get_logical_path(path, shell);
	update_pwd_vars(pwd, new_logical_path, shell);
	free(new_logical_path);
	return (0);
}
