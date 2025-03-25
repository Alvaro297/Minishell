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
		printf("%s\n", path);
		if (execve(path, cmd->args, split_envs) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			minishell->last_exit_status = 127;
			ft_putendl_fd(cmd->args[0], 2);
			exit(127);
		}
	}
}

void	no_pipes(t_minishell *minishell)
{
	int	fd;
	pid_t	pid;

	if (minishell->cmds->infile)
	{
		fd = open_f(minishell->cmds->infile, 0);
		dup2(fd, STDIN_FILENO);
		close(STDIN_FILENO);
	}
	if (minishell->cmds->outfile)
	{
		fd = open_f(minishell->cmds->outfile, 1);
		dup2(fd, STDOUT_FILENO);
		close(STDOUT_FILENO);
	}
	if (is_builtin(minishell->cmds))
		internal_commands(minishell->cmds, minishell);
	else
	{
		pid = fork();
		if (!pid)
			execute(minishell, minishell->cmds);
		else
			waitpid(pid, &minishell->last_exit_status, 0);
	}
}

void	redir(int *p_fd, t_minishell *minishell, int i)
{
	int	fd;

	if (minishell->cmds->infile)
	{
		printf("INFILE\n");
		fd = open_f(minishell->cmds->infile, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (minishell->cmds->outfile)
	{
		printf("OUTFILE\n");
		fd = open_f(minishell->cmds->outfile, 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (i < minishell->howmanycmd - 1)
	{
		if (dup2(p_fd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed(output)");
			return ;
		}
		close(p_fd[i * 2 + 1]);
	}
	if (i > 0)
	{
		if (dup2(p_fd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("dup2 failed (input)");
			return ;
		}
		close(p_fd[(i - 1) * 2]);
	}
}

void	closefds(int *fd, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->howmanycmd - 1)
	{
		close(fd[i * 2]);
		close(fd[i * 2 + 1]);
		i++;
	}
}

void	pipex(t_minishell *minishell)
{
	pid_t pid[minishell->howmanycmd];
	int		fd[(minishell->howmanycmd - 1) * 2];
	int		i;
	t_cmd	*cmd;

	cmd = minishell->cmds;
	if (minishell->howmanycmd == 0)
		return ;
	if (minishell->howmanycmd == 1)
	{
		no_pipes(minishell);
		return ;
	}
	else
	{
		i = 0;
		while (i < minishell->howmanycmd - 1)
		{
			if (pipe(fd + i * 2) == -1)
			{
				perror("error pipex\n");
				break ;
			}
			i++;
		}
		i = 1;//TODO solo funciona si entro coon i = 1 por tanto tengo que usar no_pipes o similar para ejecutar ell primer comando y redirigirlo
		while (i < minishell->howmanycmd)
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				perror("error en el foork\n");
				break ;
			}
			if (pid[i] == 0)
			{
				redir(fd, minishell, i);
				closefds(fd, minishell);
				execute(minishell, cmd);
			}
			i++;
			cmd = cmd->next;
		}
		closefds(fd, minishell);
		i = 0;
		while (i < minishell->howmanycmd)
		{
			waitpid(pid[i], &minishell->last_exit_status, 0);
			i++;
		}
	}
}
