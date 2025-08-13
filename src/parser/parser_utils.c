/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:06:17 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 16:58:19 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->path = NULL;
	cmd->delim = NULL;
	cmd->next = NULL;
	cmd->is_infile = 0;
	cmd->here_doc = 0;
	cmd->append = 0;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->prev_fd = -1;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
}

void	add_arg(t_list **args_list, char *value, char quote_type, 
		t_shell *shell)
{
	t_list	*new_node;
	char	*expanded_value;
	t_list	*env_list;

	env_list = NULL;
	if (shell)
		env_list = shell->env_list;
	expanded_value = expand_env_vars_quoted(value, quote_type, env_list);
	if (!expanded_value)
		expanded_value = ft_strdup(value);
	new_node = ft_lstnew(expanded_value);
	if (!new_node)
	{
		free(expanded_value);
		return ;
	}
	ft_lstadd_back(args_list, new_node);
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		close_all_fds(cmd);
		free(cmd->cmd);
		free_array(cmd->args);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->path)
			free(cmd->path);
		if (cmd->delim)
			free(cmd->delim);
		free(cmd);
		cmd = next;
	}
}

void	set_redir_flags(t_cmd *cmd, int redir_type)
{
	if (redir_type == REDIR_IN)
		cmd->is_infile = 1;
	else if (redir_type == REDIR_APPEND)
		cmd->append = 1;
	else if (redir_type == REDIR_HERE_DOC)
		cmd->here_doc = 1;
}
