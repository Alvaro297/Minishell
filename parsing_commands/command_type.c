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

static void	internal_commands(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmds, "exit", 4) == 0)
		exit(0);
	else if (ft_strncmp(minishell->cmds, "pwd", 3) == 0)
		handle_pwd(minishell);
	else if (ft_strncmp(minishell->cmds, "cd", 2) == 0)
		handle_cd(minishell);
	else if (ft_strncmp(minishell->cmds, "export", 7) == 0)
		handle_export(minishell);
	else if (ft_strncmp(minishell->cmds, "unset", 5) == 0)
		handle_unset(minishell);
	else if (ft_strncmp(minishell->cmds, "env", 3) == 0)
		handle_env(minishell);
	else if (ft_strncmp(minishell->cmds, "echo", 4) == 0)
		handle_echo(minishell);
}

bool	is_builtin(t_cmd	*builtin)
{
	if (ft_strncmp(builtin->cmd, "exit", 4) == 0 ||
		ft_strncmp(builtin->cmd, "pwd", 3) == 0 ||
		ft_strncmp(builtin->cmd, "cd", 2) == 0 ||
		ft_strncmp(builtin->cmd, "export", 6) == 0 ||
		ft_strncmp(builtin->cmd, "unset", 5) == 0 ||
		ft_strncmp(builtin->cmd, "env", 3) == 0 ||
		ft_strncmp(builtin->cmd, "echo", 4) == 0)
		return (true);
	return (false);
}

void	command_type(t_minishell *minishell)
{
	//Estos son los comandos internos todavia hasy muchos mas tipos de comandos que son:
	//Todo este tipo de comandos irán aquí
	int		count;
	char	*result;

	count = 0;
	while (minishell->cmds)
	{
		if (is_builtin(minishell->cmds) && count == 0)
			internal_commands(minishell);
		else if (!is_builtin(minishell->cmds))
			execute_external(minishell->cmds, minishell->env_vars);
	}
}
