/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 04:04:10 by paperez-          #+#    #+#             */
/*   Updated: 2025/02/13 13:16:58 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

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
	//	printf("%s\n", path);
		if (execve(path, cmd->args, split_envs) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			minishell->last_exit_status = 127;

			ft_putendl_fd(cmd->args[0], 2);
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
	int fdo;
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
/*
void	no_pipes(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	int		stdo;
	int 	stdi;
	int 	heredoc_fd;
	char	*string_exit_status;

	stdo = dup(STDOUT_FILENO);
	stdi = dup(STDIN_FILENO);
	redirimput(minishell->cmds);
	rediroutput(minishell->cmds);
	if (minishell->cmds->here_doc_delim && minishell->cmds->is_heredoc)
	{
		heredoc_fd = handle_heredoc(minishell, minishell->cmds->here_doc_delim, minishell->heredoc_sd);
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	if (is_builtin(minishell->cmds))
	{
		minishell->last_exit_status = internal_commands(minishell->cmds, minishell);
		string_exit_status = ft_itoa(minishell->last_exit_status);
		set_env(&minishell->env_vars, "?", string_exit_status);
		free(string_exit_status);
	}
	else
	{
		signals_ignore();
		pid = fork();
		if (!pid)
			execute(minishell, minishell->cmds);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				minishell->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minishell->last_exit_status = WTERMSIG(status) + 128;
			else
				minishell->last_exit_status = 1;
			set_env(&minishell->env_vars, "?",
				ft_itoa(minishell->last_exit_status));
		}
		signals_default();
	}
	dup2(stdo, STDOUT_FILENO);
	dup2(stdi, STDIN_FILENO);
	close (stdo);
	close (stdi);
}
*/
