/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:30:00 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/12 14:21:49 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	**list_to_array(t_list *lst)
{
	int		count;
	int		i;
	char	**array;

	i = 0;
	count = ft_lstsize(lst);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup((char *)lst->content);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}
