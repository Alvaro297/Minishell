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

int	g_signal = 0;

static bool	exit_minishell(char *input, int interactive)
{
	if (input == NULL)
	{
		if (interactive)
			printf("exit\n");
		return (true);
	}
	if (ft_strcmp(input, "exit") == 0)
		return (true);
	return (false);
}

void	minishell(char **envp)
{
	char		*input;
	t_minishell	minishell;
	int			interactive;

	init_minishell(&minishell);
	load_history(&minishell);
	manage_signals();
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
			input = readline("Minishell: ");
		else
			input = get_next_line(STDIN_FILENO);
		if (exit_minishell(input, interactive))
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
	if (argc >= 2 || ft_strcmp(argv[0], "./minishell"))
	{
		printf("Bad arguments in the program\n");
		return (EXIT_SUCCESS);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}
