/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:20:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/12 12:39:37 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_list *env_list, char *key)
{
	t_list	*current;
	t_env	*env_var;

	if (!env_list || !key)
		return (NULL);
	current = env_list;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(key)) == 0 
			&& ft_strlen(env_var->key) == ft_strlen(key))
			return (env_var);
		current = current->next;
	}
	return (NULL);
}

int	ft_env(char **args, t_shell *shell)
{
	t_list	*current;
	t_env	*env_var;

	if (args[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	current = shell->env_list;
	while (current)
	{
		env_var = (t_env *)current->content;
		printf("%s=%s\n", env_var->key, env_var->value);
		current = current->next;
	}
	return (0);
}
