/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 20:03:57 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-24 20:03:57 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_minishell(t_minishell *minishell)
{
	minishell->env_vars = NULL;
	minishell->history = NULL;
	minishell->current_dir = NULL;
	minishell->input = NULL;
	minishell->cmds = NULL;
	minishell->output = NULL;
	minishell->pids = NULL;
	minishell->history_file = get_history_file();
	minishell->here_doc_delim = NULL;
	minishell->heredoc_sd = false;
	minishell->howmanycmd = 0;
	minishell->last_exit_status = 0;
}

static bool	exitMinishell(char *input)
{
	if(ft_strcmp(input, "exit") == 0)
		return (true);
	if (input == NULL)
	{
		printf("exit\n");
		return (true);
	}
	return (false);
}

void	minishell(char **envp)
{
	char		*input;
	t_minishell	minishell;

	init_minishell(&minishell);
	load_history(&minishell);
	manage_signals();
	while (1)
	{
		input = readline("Minishell: ");
		if (exitMinishell(input))
		{
			free(input);
			break ;
		}
		fill_minishell(input, &minishell, envp);
		//error_management(&minishell);
		if (minishell.cmds == NULL)
			continue ;
		execute_all(&minishell);
		free(input);
	}
	free_all(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2 || ft_strcmp(argv[0],"./Minishell"))
	{
		printf("Bad arguments in the program\n");
		return (EXIT_SUCCESS);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}
