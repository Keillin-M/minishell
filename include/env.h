/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:17:32 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/12 12:38:56 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

// Forward declaration
typedef struct s_cmd	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_expand_info
{
	char	*str;
	char	*result;
	int		*i;
	int		*j;
	t_list	*env_list;
}	t_expand_info;

typedef struct s_shell
{
	int		cmd_count;
	int		should_exit;
	int		exit_status;
	t_list	*env_list;
	char	**paths;
}	t_shell;

void	init_env(t_shell *shell, char **envp);
char	**get_path(t_list *env_list);
t_env	*find_env_var(t_list *env_list, char *key);
int		cmd_path(t_cmd *cmd_list, char **paths);

/* Export functions */
void	add_or_update_env(t_shell *shell, char *key, char *value);
int		export_without_value(char *arg, t_shell *shell);
int		export_with_value(char *arg, t_shell *shell);

#endif
