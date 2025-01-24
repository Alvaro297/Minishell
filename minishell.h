#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_minishell/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

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
    char	**env_vars;
    char	*current_dir;
    bool	is_interactive;
} t_minishell;

void	command_tipe(t_minishell *minishell, char **envp);
void	fill_minishell(char *input, t_minishell *minishell);

#endif 