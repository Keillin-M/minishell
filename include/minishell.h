/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:45 by tthajan           #+#    #+#             */
/*   Updated: 2025/08/14 11:51:04 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"
# include "token.h"
# include "cmd.h"
# include "env.h"

// Global variable for signal handling
extern int	g_signal;

// Built-in function declarations
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_shell *shell);
int		is_valid_identifier(char *str);
void	print_invalid_identifier_error(char *command, char *identifier);
t_env	*find_env_var(t_list *env_list, char *key);
void	print_command_error(char *cmd, int error_type);
void	handle_exec_error(char *cmd, t_shell *shell);
void	print_file_error(char *filename);
int		ft_pwd(t_shell *shell);
int		ft_echo(char **args);
int		ft_exit(char **args);
int		ft_env(char **args, t_shell *shell);
int		ft_cd(char **args, t_shell *shell);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);

// Export utility functions
int		validate_export_format(char *arg, char *equal_sign);
int		validate_variable_name(char *var_name, char *equal_sign);

// CD utility functions
void	set_env_value(t_list *env_list, char *key, char *value);
char	*handle_cd_home(void);
char	*handle_cd_prev(void);
char	*get_cd_path(char **args);
void	update_pwd_vars(char *old_pwd, char *new_logical_path, t_shell *shell);

// Signal handling
void	setup_signals(void);
void	setup_child_signals(void);
void	handle_sigint(int sig);

// Utility functions
int		get_last_exit_status(void);
void	set_last_exit_status(int status);
char	*expand_env_vars(char *str, t_list *env_list);
char	*expand_env_vars_quoted(char *str, char quote_type, t_list *env_list);
void	error_exit(t_shell *shell, t_cmd *cmd, char *msg);
void	ft_clean(t_cmd *cmd, t_shell *shell);
void	close_all_fds(t_cmd *cmd);
void	free_array(char **array);
char	**list_to_array(t_list *lst);
char	*extract_var_name(char *str, int *len);
char	*get_var_value(char *var_name, t_list *env_list);
char	*get_env_from_list(t_list *env_list, char *key);

// Redirection functions
int		redirect_input(char *filename);
int		redirect_output(char *filename);
int		redirect_append(char *filename);
int		handle_heredoc(char *delimiter, t_shell *shell);

// Pipe utilities
void	execute_command(t_cmd *cmd, t_shell *shell, char **envp);
void	handle_pipe_signal_exit(int status);
void	handle_signal_exit(int status);
void	wait_for_pipes(pid_t *pids, int cmd_count);
void	setup_pipe_execution(t_pipe_info *info, t_cmd *cmd, t_shell *shell);
void	init_pipe_info(t_pipe_info *info, pid_t *pid, t_shell *shell, 
			char **envp);
int		pipex(t_pipe_info *info);

// Exec utilities
int		init_input_files(t_cmd *cmd, t_shell *shell);
int		init_output_files(t_cmd *cmd);

// Parser helper functions
void	set_redir_flags(t_cmd *cmd, int redir_type);
int		assign_redir_file(t_cmd *cmd, int redir_type, char *filename);
int		handle_token(t_list **tokens, t_cmd *cmd, t_shell *shell);
int		count_commands(t_cmd *cmd_list);
char	*handle_input(void);

#endif
