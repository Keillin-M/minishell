/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:10:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 16:43:21 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*env_var;
	t_env	*new_var;
	t_list	*new_node;

	env_var = find_env_var(shell->env_list, key);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
		return ;
	}
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_node = ft_lstnew(new_var);
	if (new_node)
		ft_lstadd_back(&(shell->env_list), new_node);
}

int	export_without_value(char *arg, t_shell *shell)
{
	(void)shell;
	if (!is_valid_identifier(arg))
	{
		print_invalid_identifier_error("export", arg);
		return (1);
	}
	return (0);
}

static int	validate_export_format(char *arg, char *equal_sign)
{
	if (equal_sign == arg)
	{
		print_invalid_identifier_error("export", arg);
		return (1);
	}
	return (0);
}

static int	validate_variable_name(char *var_name, char *equal_sign)
{
	if (!is_valid_identifier(var_name))
	{
		print_invalid_identifier_error("export", var_name);
		*equal_sign = '=';
		return (1);
	}
	return (0);
}

int	export_with_value(char *arg, t_shell *shell)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;

	equal_sign = ft_strchr(arg, '=');
	if (validate_export_format(arg, equal_sign))
		return (1);
	*equal_sign = '\0';
	var_name = arg;
	var_value = equal_sign + 1;
	if (validate_variable_name(var_name, equal_sign))
		return (1);
	add_or_update_env(shell, var_name, var_value);
	*equal_sign = '=';
	return (0);
}
