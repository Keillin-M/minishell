/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:20:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/14 11:40:27 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_vars(t_shell *shell)
{
	t_list	*current;
	t_env	*env_var;

	current = shell->env_list;
	while (current)
	{
		env_var = (t_env *)current->content;
		printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		current = current->next;
	}
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

static int	process_export_arg(char **args, int *i, t_shell *shell)
{
	char	*equal_sign;
	char	*combined_arg;

	equal_sign = ft_strchr(args[*i], '=');
	if (!equal_sign)
		return (export_without_value(args[*i], shell));
	else if (equal_sign[1] == '\0' && args[*i + 1])
	{
		combined_arg = ft_strjoin(args[*i], args[*i + 1]);
		if (!combined_arg)
			return (1);
		if (export_with_value(combined_arg, shell) != 0)
		{
			free(combined_arg);
			return (1);
		}
		free(combined_arg);
		(*i)++;
		return (0);
	}
	else if (equal_sign[1] == '\0')
		return (export_with_value(args[*i], shell));
	else
		return (export_with_value(args[*i], shell));
}

int	ft_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
	{
		print_env_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args, &i, shell) != 0)
			return (1);
		i++;
	}
	return (0);
}
