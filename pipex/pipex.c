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
		fdi = open_f(cmd->infile, 0);
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
	while (cmd->outfile_array[i])
	{
		fdo = open_f(cmd->outfile_array[i], 1);
		close(fdo);
		i++;
	}
	if (cmd->outfile)
	{
		fdo = open_f(cmd->outfile, 1);
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

void	no_pipes(t_minishell *minishell)
{
//	int	fd;
	pid_t	pid;
	int	stdo;
	int stdi;

	stdo = dup(STDOUT_FILENO);
	stdi = dup(STDIN_FILENO);
	redirimput(minishell->cmds);
	rediroutput(minishell->cmds);
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
	dup2(stdo, STDOUT_FILENO);
	dup2(stdi, STDIN_FILENO);
	close (stdo);
	close (stdi);
	//close (fd);
}
/*
void	redir(int *p_fd, t_minishell *minishell, int i)
{
//	int	fd;

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
	if (i < minishell->howmanycmd)
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

pid_t	first_cmd(t_minishell *minishell, int *pfd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close (pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close (pfd[1]);
		execute(minishell, minishell->cmds);
	}
	return (pid);
}

void	pipex(t_minishell *minishell)
{
	pid_t pid[minishell->howmanycmd];
	int		*fd;
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
		fd = create_pipes(minishell);
		pid[0] = first_cmd(minishell, fd);
		i = 1;//TODO solo funciona si entro coon i = 1 por tanto tengo que usar no_pipes o similar para ejecutar ell primer comando y redirigirlo
		while (i < minishell->howmanycmd)
		{
			pid[i] = fork();
			if (pid[i] == -1)
			{
				perror("error en el fork\n");
				break ;
			}
			if (pid[i] == 0)
			{
				closefds(fd, i - 1, i + 2);
				redir(fd, minishell, i);
				execute(minishell, cmd);
			}
			i++;
			cmd = cmd->next;
		}
		closefds(fd, minishell->howmanycmd * 3, minishell->howmanycmd * 3);
		i = 0;
		while (i < minishell->howmanycmd)
		{
			waitpid(pid[i], &minishell->last_exit_status, 0);
			i++;
		}
	}
}
*/
