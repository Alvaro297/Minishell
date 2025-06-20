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
	char	*ext_command;

	ext_command = ft_strdup(cmd->args[0]);
	path = getpath(ext_command, split_envs);
	free(ext_command);
	if (!path)
	{
		error_command_external(minishell, cmd, e, split_envs);
		free(path);
	}
	signal(SIGPIPE, SIG_DFL);
	if (execve(path, cmd->args, split_envs) == -1
		|| (cmd->is_heredoc))
	{
		error_command_external(minishell, cmd, e, split_envs);
		free (path);
	}
}

void	execute_more_commands(t_minishell *minishell, t_cmd *cmd, t_exec *e)
{
	char	**split_envs;
	int		ret;

	split_envs = returntoenvp(minishell->env_vars);
	if (is_builtin(cmd))
	{
		signal(SIGPIPE, SIG_IGN);
		ret = internal_commands(cmd, minishell);
		free_double_array((void **)split_envs);
		free_exec_builtin(e, minishell);
		free_all(minishell);
		dup2(minishell->std_out, STDIN_FILENO);
		close(minishell->std_in);
		dup2(minishell->std_out, STDOUT_FILENO);
		close(minishell->std_out);
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
