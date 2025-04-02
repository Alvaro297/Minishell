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

#include "../minishell.h"

int	internal_commands(t_cmd *current_cmd, t_minishell *minishell)
{
	if (ft_strncmp(current_cmd->cmd, "exit", 4) == 0)
		return (exit(0), 0);
	else if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0)
		return (handle_pwd(current_cmd, minishell));
	else if (ft_strncmp(current_cmd->cmd, "cd", 2) == 0)
		return (handle_cd(current_cmd, minishell));
	else if (ft_strncmp(current_cmd->cmd, "export", 7) == 0)
		return (handle_export(current_cmd, minishell));
	else if (ft_strncmp(current_cmd->cmd, "unset", 5) == 0)
		return (handle_unset(current_cmd, minishell));
	else if (ft_strncmp(current_cmd->cmd, "env", 3) == 0)
		return (handle_env(current_cmd, minishell));
	else if (ft_strncmp(current_cmd->cmd, "echo", 4) == 0)
		return (handle_echo(current_cmd, minishell));
}

bool	is_builtin(t_cmd *builtin)
{
	if (ft_strcmp(builtin->cmd, "exit") == 0 ||
		ft_strcmp(builtin->cmd, "pwd") == 0 ||
		ft_strcmp(builtin->cmd, "cd") == 0 ||
		ft_strcmp(builtin->cmd, "export") == 0 ||
		ft_strcmp(builtin->cmd, "unset") == 0 ||
		ft_strcmp(builtin->cmd, "env") == 0 ||
		ft_strcmp(builtin->cmd, "echo") == 0)
	{
		return (true);
	}
	return (false);
}

/*void	command_type(t_minishell *minishell)
{
	//Estos son los comandos internos todavia hasy muchos mas tipos de comandos que son:
	//Todo este tipo de comandos irán aquí
	t_cmd	*current_cmd;

	current_cmd = minishell->cmds;
	while (minishell->cmds)
	{
		if (is_builtin(minishell->cmds))
			internal_commands(current_cmd, minishell);
		else if (!is_builtin(current_cmd))
			execute(current_cmd->args, minishell->env_vars);
		if (current_cmd->outfile)
			minishell->output = ft_strdup("");
		current_cmd = current_cmd->next;
		//Como he puesto en el readline cuando el comando tiene un outfile es como si
		//no le pasases nada al siguiente comando por eso he puesto el if
	}
}
*/