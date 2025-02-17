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

void	minishell(char **envp)
{
	char		*input;
	t_minishell	minishell;
	int			i;

	i = 0;
	load_history(&minishell);
	manage_signals();
	while (1) 
	{
		input = readline("Minishell: ");
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0 || !input)
			break ;
		fill_minishell(input, &minishell, i, envp);
		if (input && *input)
			i++;
		if (minishell.cmds == NULL)
		{
			free(input);
			continue ;
		}
		minishell.last_exit_status = error_control(&minishell);
		if (minishell.last_exit_status == 0)
			command_type(&minishell);
		free(input);
	}
	//No hay que poner argumentos en la minishell a la hora de la ejecución.
	//Desde aqui comenzamos
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		printf("Bad arguments in the program");
		return (EXIT_SUCCESS);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}
