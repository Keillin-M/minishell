/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:10:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/14 11:42:05 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_var(t_env *env_var)
{
	if (!env_var)
		return ;
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

static void	create_and_add_new_env(t_shell *shell, char *key, char *value)
{
	t_env	*new_var;
	t_list	*new_node;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (!new_var->key)
		return (free(new_var));
	new_var->value = ft_strdup(value);
	if (!new_var->value)
		return (free_env_var(new_var));
	new_node = ft_lstnew(new_var);
	if (!new_node)
		return (free_env_var(new_var));
	ft_lstadd_back(&(shell->env_list), new_node);
}

void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*env_var;
	char	*new_value;

	env_var = find_env_var(shell->env_list, key);
	if (env_var)
	{
		new_value = ft_strdup(value);
		if (new_value)
		{
			free(env_var->value);
			env_var->value = new_value;
		}
		return ;
	}
	create_and_add_new_env(shell, key, value);
}

int	validate_export_format(char *arg, char *equal_sign)
{
	if (equal_sign == arg)
	{
		print_invalid_identifier_error("export", arg);
		return (1);
	}
	return (0);
}

int	validate_variable_name(char *var_name, char *equal_sign)
{
	if (!is_valid_identifier(var_name))
	{
		print_invalid_identifier_error("export", var_name);
		*equal_sign = '=';
		return (1);
	}
	return (0);
}
