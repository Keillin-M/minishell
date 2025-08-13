/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:30:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/13 16:23:21 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	parse_redir(t_list **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;
	char	*expanded_filename;
	int		redir_type;

	tok = (t_token *)(*tokens)->content;
	redir_type = tok->type;
	set_redir_flags(cmd, redir_type);
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (1);
	tok = (t_token *)(*tokens)->content;
	if (tok->type != WORD)
		return (1);
	expanded_filename = expand_env_vars_quoted(tok->value, tok->quote_type, 
			shell->env_list);
	if (!expanded_filename)
		expanded_filename = ft_strdup(tok->value);
	if (assign_redir_file(cmd, redir_type, expanded_filename))
		return (1);
	*tokens = (*tokens)->next;
	return (0);
}

static void	process_word_tk(t_list **tokens, t_list **args_list, t_shell *shell)
{
	t_token	*tok;

	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type != WORD)
			break ;
		add_arg(args_list, tok->value, tok->quote_type, shell);
		*tokens = (*tokens)->next;
	}
}

static void	handle_word_splitting(char *expanded_cmd, t_cmd *cmd, 
			t_list **args_list, t_shell *shell)
{
	char	**words;
	int		i;

	words = ft_split(expanded_cmd, ' ');
	if (words && words[0])
	{
		cmd->cmd = ft_strdup(words[0]);
		add_arg(args_list, cmd->cmd, 0, shell);
		i = 1;
		while (words[i])
		{
			if (words[i][0] != '\0')
				add_arg(args_list, words[i], 0, shell);
			i++;
		}
		free_array(words);
		free(expanded_cmd);
	}
	else
	{
		cmd->cmd = expanded_cmd;
		add_arg(args_list, cmd->cmd, 0, shell);
		if (words)
			free_array(words);
	}
}

static void	parse_args(t_list **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;
	t_list	*args_list;
	char	*expanded_cmd;

	args_list = NULL;
	if (!tokens || !*tokens || !(*tokens)->content)
		return ;
	tok = (t_token *)(*tokens)->content;
	if (!tok->value)
		return ;
	expanded_cmd = expand_env_vars_quoted(tok->value, tok->quote_type, 
			shell->env_list);
	if (!expanded_cmd)
		expanded_cmd = ft_strdup(tok->value);
	if (tok->quote_type == 0 && ft_strchr(expanded_cmd, ' '))
		handle_word_splitting(expanded_cmd, cmd, &args_list, shell);
	else
	{
		cmd->cmd = expanded_cmd;
		add_arg(&args_list, cmd->cmd, 0, shell);
	}
	*tokens = (*tokens)->next;
	process_word_tk(tokens, &args_list, shell);
	cmd->args = list_to_array(args_list);
	ft_lstclear(&args_list, free);
}

int	handle_token(t_list **tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*tok;

	tok = (t_token *)(*tokens)->content;
	if (tok->type == REDIR_IN || tok->type == REDIR_OUT
		|| tok->type == REDIR_APPEND || tok->type == REDIR_HERE_DOC)
	{
		if (parse_redir(tokens, cmd, shell))
			return (1);
	}
	else if (tok->type == WORD)
	{
		parse_args(tokens, cmd, shell);
	}
	else if (tok->type == PIPE)
	{
		*tokens = (*tokens)->next;
		return (2);
	}
	else
		*tokens = (*tokens)->next;
	return (0);
}
