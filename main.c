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
	t_minishell	*minishell;
	int			i;

	i = 0;
	while (1) 
	{
		input = readline("Minishell: ");
		if (input == NULL || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			break;
		fill_minishell(input, &minishell[i]);
		command_tipe(&minishell[i], envp);
		i++;
		printf("%s\n", input);
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
