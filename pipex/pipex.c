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

static void	handle_external_command(t_minishell *minishell, t_cmd *cmd,
		t_exec *e, char **split_envs)
{
	char	*path;

	path = getpath(ft_strdup(cmd->args[0]), split_envs);
	if (execve(path, cmd->args, split_envs) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		minishell->last_exit_status = 127;
		ft_putendl_fd(cmd->args[0], 2);
		free(path);
		free_double_array((void **)split_envs);
		free_exec(e, minishell);
		free_all(minishell);
		close(minishell->std_in);
		close(minishell->std_out);
		exit(127);
	}
}

void	execute_more_commands(t_minishell *minishell, t_cmd *cmd, t_exec *e)
{
	char	**split_envs;
	int		ret;

	split_envs = returntoenvp(minishell->env_vars);
	if (is_builtin(cmd))
	{
		ret = internal_commands(cmd, minishell);
		free_double_array((void **)split_envs);
		free_all(minishell);
		dup2(minishell->std_out, STDIN_FILENO);
		close(minishell->std_in);
		dup2(minishell->std_out, STDOUT_FILENO);
		close(minishell->std_out);
		free_exec(e, minishell);
		exit(ret);
	}
	else
		handle_external_command(minishell, cmd, e, split_envs);
}

int	redirimput(t_cmd *cmd)
{
	int	fdi;

	if (cmd->infile)
	{
		fdi = open_f(cmd->infile, 0, cmd);
		if (fdi < 0)
		{
			perror("open");
			return (false);
		}
		if (dup2(fdi, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (false);
		}
		close(fdi);
	}
	return (true);
}

static bool	open_all_outfiles(char **outfile_array, t_cmd *cmd)
{
	int	fdo;
	int	i;

	i = 0;
	while (outfile_array && outfile_array[i])
	{
		fdo = open_f(outfile_array[i], 1, cmd);
		if (fdo < 0)
		{
			perror("open");
			return (false);
		}
		close(fdo);
		i++;
	}
	return (true);
}

bool	rediroutput(t_cmd *cmd)
{
	int	fdo;

	if (!open_all_outfiles(cmd->outfile_array, cmd))
		return (false);
	if (cmd->outfile)
	{
		fdo = open_f(cmd->outfile, 1, cmd);
		if (fdo < 0)
		{
			perror("open");
			return (false);
		}
		if (dup2(fdo, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fdo);
			return (false);
		}
		close(fdo);
	}
	return (true);
}
