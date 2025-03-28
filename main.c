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
	int			i;

	i = 0;
	load_history(&minishell);
	manage_signals();
	init_minishell(&minishell);
	while (1)
	{
		input = readline("Minishell: ");
		if (exitMinishell(input))
			break ;
		fill_minishell(input, &minishell, i, envp);
		//error_management(&minishell);
//		if (input && *input)
//			i++;
		if (minishell.cmds == NULL)
		{
			free(input);
			continue ;
		}
		/*printf("ES BUITIN?: %s\n", minishell.cmds->cmd);
		if (is_builtin(minishell.cmds))
		{
			printf("BUILTIN\n");
			internal_commands(minishell.cmds, &minishell);
		}*/
		//minishell.last_exit_status = error_control(&minishell);
		//if (minishell.last_exit_status == 0)
		execute_all(&minishell);
		free(input);
	}
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
