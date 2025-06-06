/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:30:26 by paperez-          #+#    #+#             */
/*   Updated: 2025/06/06 17:56:09 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_execution(t_minishell *minishell, t_cmd *cmd,
		char **split_envs, char *command)
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
	ft_putstr_fd("pipex: command not found:", 2);
	minishell->last_exit_status = 127;
	free_all(minishell);
	closestd(minishell);
	free_double_array((void **)split_envs);
	exit(127);
}

void	error_comand(t_minishell *minishell, t_exec *e)
{
	free_all(minishell);
	free_exec(e, minishell);
	dup2(minishell->std_in, STDIN_FILENO);
	close(minishell->std_in);
	dup2(minishell->std_out, STDOUT_FILENO);
	close(minishell->std_out);
	exit(1);
}

void	error_command_external(t_minishell *minishell, t_cmd *cmd,
		t_exec *e, char **split_envs)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	minishell->last_exit_status = 127;
	ft_putendl_fd(cmd->args[0], 2);
	free_double_array((void **)split_envs);
	free_exec(e, minishell);
	free_all(minishell);
	close(minishell->std_in);
	close(minishell->std_out);
	exit(127);
}
