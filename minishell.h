#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/history.h>
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
#include <errno.h>

# define INVALID_CHARACTERS "!@#$%^&*()-+=[]{}\\|;:'\",.<>/?`~ "
# define INVALID_CHARACTERSV "!@#$%^&*()[]{}\\|;:'\",.<>/?`~ "
# define PATH_MAX 260
# define HISTORY_FILE "/minishell_history"

typedef struct s_indices
{
	size_t i;
	size_t j;
} t_indices;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		is_readonly;
	struct s_env *next;
} t_env;

typedef struct s_cmd
{
	char	*cmd;          // Nombre del comando (ej: "ls", "echo", "grep", etc.)
	char	**args;        // Argumentos del comando
	char	*infile;       // Archivo de entrada si hay redirección (<)
	char	*outfile;      // Archivo de salida si hay redirección (>)
	char	**outfile_array;
	int		outfile_modes;        // 2 si es ">>", 1 si es ">" y 0 si no hay nada
	bool	is_pipe;       // True si este hay una tuberia despues del comando
	struct s_cmd *next;    // Siguiente comando (si hay pipes)
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
	int		howmanycmd;
} t_minishell;

int	ft_strcmp(char *s1, char *s2);
void	command_type(t_minishell *minishell);
//** Fill_minishell **//
void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp);
/* Expand_variable */
char	*ft_quote_printf(t_minishell *minishell, char *str);
/* Quote */
int	ft_sd_quote_printf(char *str, bool *in_single_quote,
		bool *in_double_quote, size_t *i);
int	ft_sd_quote_printf_mod(char *str, bool *in_single_quote,
		bool *in_double_quote, size_t i);
char *ft_sd_quote_printf_mod3(char *str, bool *in_single_quote, bool *in_double_quote);
int	ft_sd_quote_printf_mod2(char **str, bool *in_single_quote, bool *in_double_quote);
//** Envp **//
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, char *name);
t_env	*get_env(t_env *env, char *var_name);
void	set_env(t_env **env, char *name, char *value);
void	delete_env(t_env **env, char *name);
bool	is_readonly(t_minishell *minishell, char *var);
//** Internal_commands **//
int		howmanycmds(char *argv);
int		handle_cd(t_cmd *current_cmd, t_minishell *minishell);
int		handle_pwd(t_cmd *current_cmd, t_minishell *minishell);
int		handle_echo(t_cmd *current_cmd, t_minishell *minishell);
int		handle_export(t_cmd *current_cmd, t_minishell *minishell);
void	print_entorn_variable(t_cmd *current_cmd, t_minishell *minishell);
int		handle_env(t_cmd *current_cmd, t_minishell *minishell);
int		handle_unset(t_cmd *current_cmd, t_minishell *minishell);
int		error_management(t_minishell *minishell);
//** Parsing Input **//
t_cmd	*parsing_input(t_minishell *minishell, char *input);
bool	check_name_arg(char	*name);
bool	is_builtin(t_cmd	*builtin);
void	internal_commands(t_cmd *current_cmd, t_minishell *minishell);
char	**split_modified(char *command, int c);
//** Cmds **//
char	**get_outfiles(char **command_splited);
void	delete_cmds(t_cmd *cmd);
void append_cmds(t_cmd *cmds, t_cmd *new_cmd);
char	*find_command(char **command_splited);
char	**find_args(char **command_splited);
char	*find_infile(char **command_splited);
char	*find_outfile(char **command_splited);
int		is_append(char **command_splited);
bool	have_pipe(char **command, int position);
//** History **//
void	load_history(t_minishell *minishell);
void	add_to_history(t_minishell *minishell, char *input);
//** Signals **//
void	manage_signals(void);
void	handle_sigint(int sig);
//** Free Minishell **//
void	free_double_aray(void **double_array);
#endif 
