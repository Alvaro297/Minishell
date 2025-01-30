#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_minishell/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

# define INVALID_CHARACTERS "!@#$%^&*()-+=[]{}\\|;:'\",.<>/?`~ "
# define INVALID_CHARACTERSV "!@#$%^&*()[]{}\\|;:'\",.<>/?`~ "

typedef struct s_indices
{
	size_t i;
	size_t j;
} t_indices;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_minishell
{
	char	*input;
	char	**parsed_input;
	bool	pipe;
	pid_t	*pids;
	bool	second_plane;
	char	*output;
	char	*error_message;
	char	**history;
	t_env	*env_vars;
	char	*current_dir;
	bool	is_interactive;
} t_minishell;

void	command_tipe(t_minishell *minishell, char **envp);
void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp);
int		handle_echo(t_minishell *minishell);
//** Envp **//
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, const char *name);
void	set_env(t_env **env, const char *name, const char *value);
#endif 