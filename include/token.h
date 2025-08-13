/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:06:32 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/11 17:23:42 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_tok
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC
}	t_TokenType;

typedef struct s_token
{
	t_TokenType	type;
	char		*value;
	char		quote_type;
}	t_token;

t_list	*tokenize(const char *input);
void	free_tokens(t_list *token_list);
char	**list_to_array(t_list *tokens);
void	str_op(t_list **tokens, char **temp);
int		token_size(char *s, char quote);
void	add_token(t_list **tokens, t_token *token);
char	*str_extract(char **temp);
char	*extract_word(char **temp, char *quote_type);

#endif
