/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 20:43:55 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 20:43:55 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft_minishell/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

# define INVALID_CHARACTERS "!@#$%^&*()-+=[]{}\\|;:'\"<>/?`~ "
# define INVALID_CHARACTERSV "!@#$%^&*()[]{}\\|;:'\",.<>/?`~ "
# define TMP_HEREDOC "/tmp/.heredoc_tmp"

typedef struct s_indices
{
	size_t	i;
	size_t	j;
}	t_indices;

typedef struct s_exec
{
	int		**pfd;
	int		*heredoc_fds;
	pid_t	*pids;
	int		i;
	int		j;
}	t_exec;

typedef struct s_quotes
{
	bool	in_single_quote;
	bool	in_double_quote;
}	t_quotes;

typedef struct s_parse_data
{
	char	*command;
	int		position;
	char	**array_commands;
	char	*input;
}	t_parse_data;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	char			**outfile_array;
	int				outfile_modes;
	bool			is_heredoc;
	char			**here_doc_delim;
	bool			is_pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char	*input;
	t_cmd	*cmds;
	pid_t	*pids;
	char	*output;
	char	**history;
	t_env	*env_vars;
	char	*current_dir;
	char	*history_file;
	int		last_exit_status;
	bool	heredoc_sd;
	int		howmanycmd;
	int		howmanyhd;
	int		std_in;
	int		std_out;
}	t_minishell;

typedef struct s_quote_ctx
{
	t_minishell	*minishell;
	t_quotes	*quotes;
	t_indices	*indices;
	char		**result;
}	t_quote_ctx;

extern int	g_signal;

int		ft_strcmp(char *s1, char *s2);
//void	command_type(t_minishell *minishell);
//** Fill_minishell **//
void	fill_minishell(char *input, t_minishell *minishell, char **envp);
void	free_all(t_minishell *minishell);
char	*get_history_file(void);
void	set_special_var(t_minishell *minishell);
void	set_special_var_input_null(t_minishell *minishell, char *result);
void	ft_quote_printf_cleanup(t_minishell *minishell, t_quotes quotes,
			char **result, bool is_input);
/* Expand_variable */
char	*ft_quote_printf(t_minishell *minishell, char *str, bool is_input);
void	append_expanded_variable(char **result, size_t *j, char *expanded);
void	append_expanded_variable_no_quotes(char **result,
			size_t *j, char *expanded);
/* Quote */
int		ft_sd_quote_printf(char *str, t_quotes *quotes, size_t *i);
int		ft_sd_quote_printf_mod(char *str, t_quotes *quotes, size_t i);
void	ft_sd_quote_printf_mod3(char *str, t_quotes *quotes);
char	*delete_quotes_array(t_minishell *minishell, char *array,
			bool is_not_here_doc, bool is_iofile);
//** Envp **//
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, char *name, bool free_var);
t_env	*get_env(t_env *env, char *var_name);
t_env	*create_env_var(char *name, char *value);
t_env	*find_env_var(t_env *env, char *name);
char	*trim_quotes(char *value);
void	set_env(t_env **env, char *name, char *value);
void	delete_env(t_env **env, char *name);
bool	is_env_var_null(t_minishell *minishell, char *arg);
char	*init_shlvl(void);
t_env	*init_env_without_env(void);
//** Internal_commands **//
int		howmanycmds(t_cmd *cmd);
int		handle_cd(t_cmd *current_cmd, t_minishell *minishell);
int		handle_pwd( t_minishell *minishell);
int		handle_echo(t_cmd *current_cmd, t_minishell *minishell);
int		handle_exit(t_cmd *cmd, t_minishell *minishell);
int		handle_export(t_cmd *current_cmd, t_minishell *minishell);
int		handle_env(t_cmd *current_cmd, t_minishell *minishell);
int		handle_unset(t_cmd *current_cmd, t_minishell *minishell);
int		export_one_var(t_cmd *cmd, t_minishell *mini, int i);
void	print_entorn_variable(t_minishell *minishell);
bool	parsed_name_validation(char *var_name);
char	*parsed_variable_name(char *str);
//** Parsing Input **//
char	*tabs_to_spaces(char *str);
void	delete_quotes(t_minishell *minishell, t_cmd *cmd);
t_cmd	*parsing_input(t_minishell *minishell, char *input);
void	fill_cmd_fields(t_minishell *minishell, t_cmd *tmp,
			char **command_splited, t_parse_data *data);
bool	is_in_sd_quotes(t_cmd *cmds);
bool	check_name_arg(char	*name);
bool	is_builtin(t_cmd	*builtin);
int		internal_commands(t_cmd *current_cmd, t_minishell *minishell);
char	**split_modified(char *command, int c);
bool	is_heredoc(char **command_splited);
char	**here_doc_delim(char *input);
int		ft_count_heredocs(char **command_splited);
bool	is_redirected(char *command_splited);
int		ft_count_command_splited(char **command_splited);
int		ft_count_newarray(char **command_splited, int i,
			t_quotes *quotes, int count_total_array);
char	**process_redirection(char **command_splited);
char	**delete_quotes_double_array(t_minishell *minishell,
			char **double_array, bool is_not_here_doc);
//** Cmds **//
char	**get_outfiles(char **command_splited, int c1);
void	delete_cmds(t_cmd *cmd);
void	append_cmds(t_cmd **cmds, t_cmd *new_cmd);
char	*find_command(t_minishell *minishell, char **command_splited);
char	**find_args(t_minishell *minishell, char **command_splited);
char	*find_infile(char **command_splited);
char	*find_outfile(char **command_splited);
int		is_append(char **command_splited);
bool	have_pipe(char **command, int position);
//** Errors **//
bool	controled_errors(t_minishell *minishell,
			char **command_splited, t_parse_data *command);
void	handle_unclosed_quotes(t_minishell *minishell,
			t_quotes quotes, char **result);
bool	check_pipes(char **array_commands, int position);
//** Init Minishell **//
void	init_minishell(t_minishell *minishell);
void	init_cmd(t_cmd *cmd);
//** History **//
void	load_history(t_minishell *minishell);
void	add_to_history(t_minishell *minishell, char *input);
//** Signals **//
void	manage_signals(void);
void	signals_ignore(void);
void	signals_default(void);
void	handle_sigint(int sig);
void	process_heredoc_signals(struct sigaction *sa_old,
			struct sigaction *sa_new);
int		heredoc_event_hook(void);
void	sigint_heredoc_handler(int sig);
//** Free Minishell **//
void	free_exec_builtin(t_exec *e, t_minishell *minishell);
void	free_exec(t_exec *e, t_minishell *minishell);
void	free_double_array(void **double_array);
void	free_env_list(t_env *env);
void	free_cmd_list(t_cmd *cmd);
void	closestd(t_minishell *minishell);
//**PIPEX **/
void	sigint_heredoc_handler(int sig);
int		process_heredoc(t_minishell *minishell,
			const char *delimiter, char *tmpfile, bool heredoc_sd);
int		handle_heredoc(t_minishell *minishell,
			char **delimiter, bool heredoc_sd);
void	error_command_external(t_minishell *minishell, t_cmd *cmd,
			t_exec *e, char **split_envs);
void	free_pipe_fds(int **pfd, int count);
void	error_comand(t_minishell *minishell, t_exec *e);
int		**create_pipes(t_minishell *minishell);
char	*ft_quote_printf_here_doc(t_minishell *minishell, char *str);
void	first_child(t_minishell *minishell, t_cmd *cmd, t_exec *e);
void	last_child(t_minishell *minishell, t_cmd *cmd, t_exec *e);
void	execute_command(t_minishell *minishell, t_cmd *cmd, t_exec *e);
void	closefds(t_minishell *minishell, int **fd);
void	execute_all(t_minishell *minishell);
int		*manage_heredocs(t_minishell *minishell);
void	redir(t_minishell *minishell);
bool	rediroutput(t_cmd *cmd);
int		redirimput(t_cmd *cmd);
void	no_pipes(t_minishell *minishell);
void	execute(t_minishell *minishell, t_cmd *cmd);
void	execute_more_commands(t_minishell *minishell, t_cmd *cmd, t_exec *e);
void	execute_all(t_minishell *minishell);
void	pipex(t_minishell *minishell);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	freeall(char **m);
void	exitaux(void);
char	**returntoenvp(t_env *env);
char	**ft_split(char const *s, char c);
char	*getpathaux(char *path, char **env);
char	*getpath(char *cmd, char **env);
int		open_f(char *file, int sw, t_cmd *cmd);
#endif 
