/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 20:04:04 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-24 20:04:04 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	internal_commands(char *input, char **envp)
{
	if (ft_strnstr(input, "exit ", 5))
		/* code */
	else if (ft_strnstr(input, "cd ", 3))
		/* code */
	else if (ft_strnstr(input, "pwd ", 4))
		/* code */
	else if (ft_strnstr(input, "export ", 8))
		/* code */
	else if (ft_strnstr(input, "unset ", 6))
		/* code */
	else if (ft_strnstr(input, "env ", 4))
		/* code */
	else if (ft_strnstr(input, "echo ", 5))
		/* code */
	
}

void	command_tipe(t_minishell *minishell, char **envp)
{
	//Estos son los comandos internos todavia hasy muchos mas tipos de comandos que son:
	//Comandos externos: ls, grep, cat, gcc
	//Redirecciones: < > >> <<
	//Pipes: |
	//Comandos en Segundo plano: &
	//Todo este tipo de comandos irán aquí
	if (ft_strncmp(minishell->input, "exit ", 5) == 0 || ft_strncmp(minishell->input, "cd ", 3) == 0 ||
		ft_strncmp(minishell->input, "pwd ", 4) == 0 || ft_strncmp(minishell->input, "export ", 8) == 0 ||
		ft_strncmp(minishell->input, "unset ", 6) == 0 || ft_strncmp(minishell->input, "env ", 4) == 0 ||
		ft_strncmp(minishell->input, "echo ", 5) == 0)
		internal_commands(minishell->input, envp);
	
}
