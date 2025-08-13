/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:50:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/13 16:58:19 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_input_redir(t_cmd *cmd, int redir_type, char *filename)
{
	int	fd;

	if (redir_type == REDIR_IN)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(filename);
			free(filename);
			return (1);
		}
		close(fd);
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = filename;
	}
	else if (redir_type == REDIR_HERE_DOC)
	{
		if (cmd->delim)
			free(cmd->delim);
		cmd->delim = filename;
	}
	return (0);
}

static int	assign_output_redir(t_cmd *cmd, char *filename)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
		free(cmd->outfile);
	}
	cmd->outfile = filename;
	return (0);
}

int	assign_redir_file(t_cmd *cmd, int redir_type, char *filename)
{
	if (redir_type == REDIR_IN || redir_type == REDIR_HERE_DOC)
		return (assign_input_redir(cmd, redir_type, filename));
	else
		return (assign_output_redir(cmd, filename));
}
