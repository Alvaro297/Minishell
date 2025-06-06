/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:33:31 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:33:33 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closefds(t_minishell *minishell, int **fd)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < minishell->howmanycmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	last_child(t_minishell *minishell, t_cmd *cmd, t_exec *e)
{
	int	all_ok;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	all_ok = 1;
	if (cmd->infile && !cmd->is_heredoc)
		all_ok = redirimput(cmd);
	else if (!cmd->is_heredoc)
		dup2(e->pfd[minishell->howmanycmd - 2][0], STDIN_FILENO);
	if (cmd->outfile && all_ok)
		all_ok = rediroutput(cmd);
	else
	{
		dup2(minishell->std_out, STDOUT_FILENO);
		close(minishell->std_out);
	}
	closefds(minishell, e->pfd);
	if (all_ok)
		execute_more_commands(minishell, cmd, e);
	else
		error_comand(minishell, e);
}

void	first_child(t_minishell *minishell, t_cmd *cmd, t_exec *e)
{
	int	all_ok;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	all_ok = 1;
	if (cmd->infile)
		all_ok = redirimput(cmd);
	if (cmd->outfile && all_ok)
		all_ok = rediroutput(cmd);
	else
		dup2(e->pfd[0][1], STDOUT_FILENO);
	closefds(minishell, e->pfd);
	if (all_ok)
		execute_more_commands(minishell, cmd, e);
	else
		error_comand(minishell, e);
}

void	execute_command(t_minishell *minishell, t_cmd *cmd, t_exec *e)
{
	int	all_ok;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	all_ok = 1;
	if (cmd->infile && !cmd->is_heredoc)
		all_ok = redirimput(cmd);
	else if (!cmd->is_heredoc)
		dup2(e->pfd[e->i - 1][0], STDIN_FILENO);
	if (cmd->outfile && all_ok)
		all_ok = rediroutput(cmd);
	else
		dup2(e->pfd[e->i][1], STDOUT_FILENO);
	closefds(minishell, e->pfd);
	if (all_ok)
		execute_more_commands(minishell, cmd, e);
	else
		error_comand(minishell, e);
}

int	**create_pipes(t_minishell *minishell)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int *) * (minishell->howmanycmd - 1));
	while (i < minishell->howmanycmd - 1)
	{
		fd[i] = malloc (sizeof(int) * 2);
		if (pipe(fd[i]) != 0)
		{
			perror("pipe error");
			return (NULL);
		}
		i++;
	}
	return (fd);
}
