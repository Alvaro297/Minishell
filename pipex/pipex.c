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

void	execute(t_minishell minishell, t_cmd *cmd)
{
	char	**split_cmd;
	char	*path;
	
	if (is_builtin(cmd))
		internal_commands(cmd, minishell);
	else
	{
		split_cmd = ft_split(cmd->args, ' ');
		path = getpath(split_cmd[0], minishell->env__vars);
		if (execve(path, split_cmd, minishell->env_vars) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(split_cmd[0], 2);
			freeall(split_cmd);
			exit(0);
		}
	}
}

void	child(t_cmd *cmd, t_minishell minishell, int *p_fd)
{
	int	fd;

	if(cmd->infile != NULL)
	{
		fd = open_f(cmd->infile, 0);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDIN_FILENO);
	}
	dup2(p_fd[1], STDOUT_FILENO);
	close (p_fd[0]);
	execute(minishell, cmd);
}

void	parent(t_cmd *cmd, t_minishell minishell, int *p_fd)
{
	int	fd;
	t_cmd *next;
	int	tmp_fd[2];
	int	pid;

	next = cmd->next;
	if(cmd->outfile != NULL)
	{
		fd = open_f(cmd->outfile, 1);
		if (fd == -1)
			exit(0);
		dup2(fd, STDOUT_FILENO);
	}
	if (next == NULL || !next->is_pipe)
	{
		dup2(tmp_fd[0], STDIN_FILENO);
		close (p_fd[1]);
		execute(minishell, cmd);
	}
}

int	pipex(t_minishell *minishell)
{
	pid_t	pid[minishell->howmanycmd];
	int		p_fd[2 * (minishell->howmanycmd - 1)];
	t_cmd	cmd;
	int		count;
	int		i;

	i = 0;
	count = howmanycmds(minishell->input);//TODO comprobar que los pipes no estan entrecomillados
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
		if (count == 0 && isbuiltin(cmd))
			break;
	    pid[i] = fork();
        if (pid == -1)
		    exit (-1);
        if (!pid)
			child(cmd, minishell);
		close (p_fd[i + 1]);
		cmd = cmd->next;
		count--;
    }
	parent(cmd, minishell);
	return (0);
}
