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
	
	split_envs = ft_split(minishell->input, '\n');//TODO convertir t_env en char**
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
			exit(127);
		}
	}
}

void	child(t_cmd *cmd, t_minishell *minishell, int *p_fd)
{
	int	fd;

	if(cmd->infile != NULL)
	{
		fd = open_f(cmd->infile, 0);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(p_fd[1], STDOUT_FILENO);
	close (p_fd[0]);
	execute(minishell, cmd);
}

void	parent(t_cmd *cmd, t_minishell *minishell, int *p_fd)
{
	int	fd;

	if(cmd->outfile != NULL)
	{
		fd = open_f(cmd->outfile, 1);
		if (fd == -1)
			exit(0);
		dup2(fd, STDOUT_FILENO);
	}
	dup2(p_fd[0], STDIN_FILENO);
	close (p_fd[1]);
	execute(minishell, cmd);
}

int	pipex(t_minishell *minishell)
{
	pid_t	pid[minishell->howmanycmd];
	int		p_fd[2 * (minishell->howmanycmd - 1)];
	t_cmd	*cmd;
	int		count;
	int		i;

	i = 0;
	count = minishell->howmanycmd;
	printf("PIPEX\n");
	if (is_builtin(minishell->cmds))
	{
		internal_commands(minishell->cmds, minishell);
		return(0);
	}
	while (i < count - 1)
	{
		if (pipe(p_fd + i * 2) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
	i = 0;
	cmd = minishell->cmds;
	while (i < count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit (-1);
		if (!pid[i])
			child(cmd, minishell, p_fd + i * 2);
		close (p_fd[i + 1]);
		cmd = cmd->next;
		i++;
	}
	parent(cmd, minishell, &i);
	i = 0;
	while (pid[i])
	{
		if (waitpid(pid[i], NULL, 0) != 0)
		{
			minishell->last_exit_status = waitpid(pid[i], NULL, 0);
			break;
		}
		i++;
	}
	return (0);
}
