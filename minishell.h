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

# define INVALID_CHARACTERS "!@#$%^&*()-+=[]{}\\|;:'\"<>/?`~ "
# define INVALID_CHARACTERSV "!@#$%^&*()[]{}\\|;:'\",.<>/?`~ "
# define HISTORY_FILE "./minishell_history"

typedef struct s_indices
{
	size_t	i;
	size_t	j;
} t_indices;

typedef struct s_quotes
{
	bool	in_single_quote;
	bool	in_double_quote;
} t_quotes;

typedef struct s_parse_data
{
	char	*command;
	int		position;
	char	**array_commands;
	char	*input;
}	t_parse_data;


typedef struct s_env
{
	char	*name;          // Nombre de la variable de entorno (ej: "PATH", "HOME").
	char	*value;         // Valor de la variable de entorno (ej: "/usr/bin", "/home/user").
	struct s_env *next; // Puntero al siguiente nodo en la lista enlazada de variables de entorno.
} t_env;

typedef struct s_cmd
{
	char	*cmd;          // Nombre del comando (ej: "ls", "echo", "grep").
	char	**args;        // Array de argumentos del comando (ej: ["ls", "-l", NULL]).
	char	*infile;       // Archivo de entrada para redirección (<).
	char	*outfile;      // Archivo de salida para redirección (> o >>).
	char	**outfile_array; // Array de archivos de salida si hay múltiples redirecciones.
	int		outfile_modes; // Modo de redirección: 2 para ">>", 1 para ">", 0 para ninguno.
	bool	is_pipe;       // Indica si el comando está seguido por un pipe (|).
	bool	is_heredoc;	   // Indica si el comando utiliza un heredoc (<<).
	char	**here_doc_delim; // Array de delimitadores para heredoc.
	struct s_cmd *next;    // Puntero al siguiente comando en una lista enlazada (para pipes).
}	t_cmd;

typedef struct s_minishell
{
	char	*input;        // Entrada del usuario (línea de comando completa).
	t_cmd	*cmds;         // Lista enlazada de comandos parseados.
	pid_t	*pids;         // Array de PIDs para procesos hijos.
	char	*output;       // Salida del comando (si se almacena en memoria).
	char	**history;     // Historial de comandos.
	t_env	*env_vars;     // Lista enlazada de variables de entorno.
	char	*current_dir;  // Directorio actual del shell.
	char	*history_file; // Ruta al archivo de historial.
	int		last_exit_status; // Código de salida del último comando ejecutado.
	int		howmanycmd;    // Número de comandos en la línea de entrada.
} t_minishell;

int	ft_strcmp(char *s1, char *s2);
//void	command_type(t_minishell *minishell);
//** Fill_minishell **//
void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp);
/* Expand_variable */
char	*ft_quote_printf(t_minishell *minishell, char *str);
void	append_expanded_variable(char **result, size_t *j, char *expanded);
void	append_expanded_variable_no_quotes(char **result, size_t *j, char *expanded);
/* Quote */
int		ft_sd_quote_printf(char *str, t_quotes *quotes, size_t *i);
int		ft_sd_quote_printf_mod(char *str, t_quotes *quotes, size_t i);
char	*ft_sd_quote_printf_mod2(char *str, t_quotes *quotes);
void	ft_sd_quote_printf_mod3(char *str, t_quotes *quotes);
bool	is_within_quotes(const char *str, const char *pos);
//** Envp **//
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, char *name);
t_env	*get_env(t_env *env, char *var_name);
void	set_env(t_env **env, char *name, char *value);
void	delete_env(t_env **env, char *name);
bool	is_readonly(t_minishell *minishell, char *var);
bool	is_env_var_null(t_minishell *minishell, char *arg);
//** Internal_commands **//
int		howmanycmds(t_cmd *cmd);
int		handle_cd(t_cmd *current_cmd, t_minishell *minishell);
int		handle_pwd(t_cmd *current_cmd, t_minishell *minishell);
int		handle_echo(t_cmd *current_cmd, t_minishell *minishell);
int		handle_export(t_cmd *current_cmd, t_minishell *minishell);
void	print_entorn_variable(t_cmd *current_cmd, t_minishell *minishell);
int		handle_env(t_cmd *current_cmd, t_minishell *minishell);
int		handle_unset(t_cmd *current_cmd, t_minishell *minishell);
int		error_management(t_minishell *minishell);
//** Parsing Input **//
void	delete_quotes(t_minishell *minishell, t_cmd *cmd);
t_cmd	*parsing_input(t_minishell *minishell, char *input);
bool	check_name_arg(char	*name);
bool	is_builtin(t_cmd	*builtin);
int		internal_commands(t_cmd *current_cmd, t_minishell *minishell);
char	**split_modified(char *command, int c);
bool	is_heredoc(char **command_splited);
char	**here_doc_delim(char *input);
bool	is_redirected(char *command_splited);
int		ft_count_command_splited(char **command_splited);
int		ft_count_newarray(char **command_splited, int i, t_quotes *quotes, int count_total_array);
char	**process_redirection(char **command_splited);
//** Cmds **//
char	**get_outfiles(t_minishell *minishell, char **command_splited);
void	delete_cmds(t_cmd *cmd);
void	append_cmds(t_cmd **cmds, t_cmd *new_cmd);
char	*find_command(t_minishell *minishell, char **command_splited);
char	**find_args(t_minishell *minishell, char **command_splited);
char	*find_infile(t_minishell *minishell, char **command_splited);
char	*find_outfile(t_minishell *minishell, char **command_splited);
int		is_append(char **command_splited);
bool	have_pipe(char **command, int position);
//** History **//
void	load_history(t_minishell *minishell);
void	add_to_history(t_minishell *minishell, char *input);
//** Signals **//
void	manage_signals(void);
//** Free Minishell **//
void	free_double_array(void **double_array);
//**PIPEX **/
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
int		open_f(char *file, int sw);
//**  Pipex prueba**//
int		pipex_prueba(t_minishell *minishell);

#endif 