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

static void	internal_commands_help(t_minishell *minishell, char **envp)
{
	
	if (ft_strncmp(minishell->parsed_input[0], "export", 7) == 0)
		handle_export(minishell, envp);
	else if (ft_strncmp(minishell->parsed_input[0], "unset", 5) == 0)
		/* code */
	else if (ft_strncmp(minishell->parsed_input[0], "env", 3) == 0)
		/* code */
	else if (ft_strncmp(minishell->parsed_input[0], "echo", 4) == 0)
		handle_echo(minishell);
}

static void	internal_commands(t_minishell *minishell, char **envp)
{
	char	cwd[2048];

	if (ft_strncmp(minishell->parsed_input[0], "exit", 4) == 0)
		exit (0);
	else if (ft_strncmp(minishell->parsed_input[0], "pwd", 3) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("pwd");
		else
			printf("%s\n", cwd);
	}
	else if (ft_strncmp(minishell->parsed_input[0], "cd", 3) == 0)
	{
		if (chdir(parsed_input[1]) != 0)
			perror("Error:");
	}
	else
		internal_commands_help(minishell, envp);
}

void	command_tipe(t_minishell *minishell, char **envp)
{
	//Estos son los comandos internos todavia hasy muchos mas tipos de comandos que son:
	//Comandos externos: ls, grep, cat, gcc
	//Redirecciones: < > >> <<
	//Pipes: |
	//Comandos en Segundo plano: &
	//Todo este tipo de comandos irán aquí
	if (minishell->parsed_input[0] != NULL)
		internal_commands(minishell, envp);
	
}
