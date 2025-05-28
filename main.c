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

static bool	exit_minishell(char *input)
{
	if (ft_strcmp(input, "exit") == 0)
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
		if (exit_minishell(input))
		{
			free(input);
			break ;
		}
		fill_minishell(input, &minishell, envp);
		if (minishell.cmds == NULL)
			continue ;
		execute_all(&minishell);
		free(input);
	}
	free_all(&minishell);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2 || ft_strcmp(argv[0], "./Minishell"))
	{
		printf("Bad arguments in the program\n");
		return (EXIT_SUCCESS);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}
