/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:06:03 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/14 11:23:34 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_tokens(t_list *tokens)
{
	t_list	*temp;
	t_token	*token;

	while (tokens)
	{
		temp = tokens->next;
		token = (t_token *)tokens->content;
		if (token)
		{
			free(token->value);
			free(token);
		}
		free(tokens);
		tokens = temp;
	}
}

char	*str_extract(char **temp)
{
	int		size;
	char	quote;
	char	*s;
	char	*t;

	t = *temp;
	quote = *t++;
	size = token_size(t, quote);
	s = malloc(size + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, t, size);
	s[size] = '\0';
	t += size;
	if (*t == quote)
		t++;
	*temp = t;
	return (s);
}

static char	*join_word_parts(char *combined, char *part)
{
	char	*new_combined;

	if (!part)
	{
		free(combined);
		return (NULL);
	}
	new_combined = ft_strjoin(combined, part);
	free(combined);
	free(part);
	return (new_combined);
}

static void	str_word(t_list **tokens, char **temp)
{
	char	quote_type;
	char	*combined;
	char	*part;
	t_token	*token;

	quote_type = 0;
	combined = ft_strdup("");
	if (!combined)
		return ;
	while (**temp && **temp != ' ' && **temp != '\t' && **temp != '|'
		&& **temp != '>' && **temp != '<')
	{
		part = extract_word(temp, &quote_type);
		combined = join_word_parts(combined, part);
		if (!combined)
			return ;
	}
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(combined));
	token->value = combined;
	token->type = WORD;
	token->quote_type = quote_type;
	add_token(tokens, token);
}

t_list	*tokenize(const char *input)
{
	int		i;
	char	*temp;
	t_list	*tokens;

	i = 0;
	tokens = NULL;
	if (!input || !*input)
		return (NULL);
	temp = (char *)input;
	while (*temp)
	{
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if (!*temp)
			break ;
		if (*temp == '|' || *temp == '>' || *temp == '<')
			str_op(&tokens, &temp);
		else
			str_word(&tokens, &temp);
	}
	return (tokens);
}
