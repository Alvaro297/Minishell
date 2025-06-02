/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 04:04:10 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:14:30 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

void	execute_more_commands(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;
	char	**split_envs;

	split_envs = returntoenvp(minishell->env_vars);
	if (is_builtin(cmd))
	{
		int ret = internal_commands(cmd, minishell);
		free_double_array((void **) split_envs);
		free_all(minishell);
		exit(ret);
	}
	else
	{
		path = getpath(cmd->args[0], split_envs);
		if (execve(path, cmd->args, split_envs) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			minishell->last_exit_status = 127;
			ft_putendl_fd(cmd->args[0], 2);
			free(path);
			free_double_array((void **) split_envs);
			free_all(minishell);
			exit(127);
		}
	}
}

void	execute(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;
	char	**split_envs;

	split_envs = returntoenvp(minishell->env_vars);
	if (is_builtin(cmd))
		internal_commands(cmd, minishell);
	else
	{
		path = getpath(cmd->args[0], split_envs);
		if (execve(path, cmd->args, split_envs) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			minishell->last_exit_status = 127;
			ft_putendl_fd(cmd->args[0], 2);
			free(path);
			free_double_array((void **) split_envs);
			free_all(minishell);
			exit(127);
		}
	}
}

void	redirimput(t_cmd *cmd)
{
	int	fdi;

	if (cmd->infile)
	{
		fdi = open_f(cmd->infile, 0, cmd);
		if (fdi < 0)
		{
			perror("open");
			return ;
		}
		if (dup2(fdi, STDIN_FILENO) < 0)
			perror("dup2");
		close(fdi);
	}
}

void	rediroutput(t_cmd *cmd)
{
	int	fdo;
	int	i;

	i = 0;
	if (cmd->outfile_array != NULL)
	{
		while (cmd->outfile_array[i])
		{
			fdo = open_f(cmd->outfile_array[i], 1, cmd);
			close(fdo);
			i++;
		}
	}
	if (cmd->outfile)
	{
		fdo = open_f(cmd->outfile, 1, cmd);
		if (fdo < 0)
		{
			perror("open");
			return ;
		}
		if (dup2(fdo, STDOUT_FILENO) < 0)
			perror("dup2");
		close(fdo);
	}
}
