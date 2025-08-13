/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:45:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/12 12:16:55 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_expand_info	init_expansion_info(char *str, t_list *env_list)
{
	t_expand_info	info;
	char			*result;

	result = malloc(ft_strlen(str) * 8 + 1024);
	info.str = str;
	info.result = result;
	info.i = malloc(sizeof(int));
	info.j = malloc(sizeof(int));
	if (!result || !info.i || !info.j)
	{
		if (result)
			free(result);
		if (info.i)
			free(info.i);
		if (info.j)
			free(info.j);
		info.result = NULL;
		info.i = NULL;
		info.j = NULL;
		return (info);
	}
	*info.i = 0;
	*info.j = 0;
	info.env_list = env_list;
	return (info);
}

static void	process_var_expansion(t_expand_info *info)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		val_len;

	var_name = extract_var_name(&info->str[*info->i], &var_len);
	var_value = get_var_value(var_name, info->env_list);
	if (var_value)
	{
		val_len = ft_strlen(var_value);
		ft_memcpy(&info->result[*info->j], var_value, val_len);
		*info->j += val_len;
		free(var_value);
	}
	free(var_name);
	*info->i += var_len;
}

char	*expand_env_vars(char *str, t_list *env_list)
{
	t_expand_info	info;
	char			*result;

	if (!str)
		return (NULL);
	info = init_expansion_info(str, env_list);
	if (!info.result || !info.i || !info.j)
		return (NULL);
	while (str[*info.i])
	{
		if (str[*info.i] == '$' && str[*info.i + 1] && 
			(ft_isalnum(str[*info.i + 1]) || str[*info.i + 1] == '_' 
				|| str[*info.i + 1] == '?' || str[*info.i + 1] == '{'))
			process_var_expansion(&info);
		else
			info.result[(*info.j)++] = str[(*info.i)++];
	}
	info.result[*info.j] = '\0';
	result = info.result;
	free(info.i);
	free(info.j);
	return (result);
}

char	*expand_env_vars_quoted(char *str, char quote_type, t_list *env_list)
{
	if (quote_type == '\'')
		return (ft_strdup(str));
	return (expand_env_vars(str, env_list));
}
