/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:00:00 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/13 15:24:16 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	init_input_files(t_cmd *cmd, t_shell *shell)
{
	if (cmd->here_doc && cmd->delim)
	{
		cmd->in_fd = handle_heredoc(cmd->delim, shell);
		if (cmd->in_fd < 0)
			return (ft_putstr_fd("Error: could not handle heredoc\n", 2), 1);
	}
	else if (cmd->infile)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
		{
			print_file_error(cmd->infile);
			return (1);
		}
	}
	return (0);
}

int	init_output_files(t_cmd *cmd)
{
	if (cmd->outfile)
	{
		if (cmd->append)
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (cmd->out_fd < 0)
		{
			if (cmd->in_fd != -1)
				close(cmd->in_fd);
			print_file_error(cmd->outfile);
			return (1);
		}
	}
	return (0);
}
