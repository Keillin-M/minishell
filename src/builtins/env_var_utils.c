/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:00:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 12:41:21 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_from_list(t_list *env_list, char *key)
{
	t_env	*env_var;

	env_var = find_env_var(env_list, key);
	if (env_var)
		return (env_var->value);
	return (NULL);
}

char	*extract_var_name(char *str, int *len)
{
	int	i;

	i = 1;
	if (str[i] == '?')
	{
		*len = 2;
		return (ft_strdup("?"));
	}
	if (str[1] == '{')
	{
		i = 2;
		while (str[i] && str[i] != '}' && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i] == '}')
		{
			*len = i + 1;
			return (ft_substr(str, 2, i - 2));
		}
		*len = 2;
		return (ft_strdup("{"));
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*len = i;
	return (ft_substr(str, 1, i - 1));
}

char	*get_var_value(char *var_name, t_list *env_list)
{
	char	*value;

	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(get_last_exit_status()));
	if (env_list)
	{
		value = get_env_from_list(env_list, var_name);
		if (value)
			return (ft_strdup(value));
	}
	return (ft_strdup(""));
}
