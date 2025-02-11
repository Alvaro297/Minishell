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
	while (1) 
	{
		input = readline("Minishell: ");
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			break ;
		fill_minishell(input, &minishell, i, envp);
		command_type(&minishell, envp);
		if (input && *input)
			i++;
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
