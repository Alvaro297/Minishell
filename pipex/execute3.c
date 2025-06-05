/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:30:26 by paperez-          #+#    #+#             */
/*   Updated: 2025/06/03 21:17:33 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_execution(t_minishell *minishell, t_cmd *cmd, char **split_envs, char *command)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd->args[0], 2);
	minishell->last_exit_status = 127;
	free(command);
	free_double_array((void **)split_envs);
	free_all(minishell);
	closestd(minishell);
	exit(127);
}

void	execute_ext(t_minishell *minishell, t_cmd *cmd, char **split_envs)
{
	char	*path;
	char	*command;

	command = ft_strdup(cmd->args[0]);
	path = getpath(command, split_envs);
	if (!path)
		error_execution(minishell, cmd, split_envs, command);
	if (execve(path, cmd->args, split_envs) == -1)
		error_execution(minishell, cmd, split_envs, command);
	free(command);
	free(path);
}

void	execute(t_minishell *minishell, t_cmd *cmd)
{
	char	**split_envs;

	split_envs = returntoenvp(minishell->env_vars);
	if (is_builtin(cmd))
		internal_commands(cmd, minishell);
	else if (cmd->args[0])
		execute_ext(minishell, cmd, split_envs);
//	else
	//{
	ft_putstr_fd("pipex: command not found:", 2);
	minishell->last_exit_status = 127;
	free_all(minishell);
	closestd(minishell);
	free_double_array((void **)split_envs);
	exit(127);
//	}
}
