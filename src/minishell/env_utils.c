/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:53:03 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/14 11:08:25 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_var(char *env_s)
{
	int		key_len;
	char	*equal;
	t_env	*var;

	equal = ft_strchr(env_s, '=');
	if (!equal)
		return (NULL);
	key_len = equal - env_s;
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_substr(env_s, 0, key_len);
	if (!var->key)
	{
		free(var);
		return (NULL);
	}
	var->value = ft_strdup(equal + 1);
	if (!var->value)
	{
		free(var->key);
		free(var);
		return (NULL);
	}
	return (var);
}

t_list	*env_node(char *env_s)
{
	t_env	*var;
	t_list	*node;

	var = create_env_var(env_s);
	if (!var)
		return (NULL);
	node = ft_lstnew(var);
	if (!node)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	return (node);
}

void	init_env(t_shell *shell, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	shell->env_list = NULL;
	while (envp[i])
	{
		node = env_node(envp[i]);
		if (node)
			ft_lstadd_back(&shell->env_list, node);
		i++;
	}
}
