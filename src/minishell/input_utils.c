/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:30:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/11 17:19:16 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	if (input && *input)
		add_history(input);
	return (input);
}
