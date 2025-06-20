/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:33:26 by paperez-          #+#    #+#             */
/*   Updated: 2025/06/02 22:19:35 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_execution(t_minishell *minishell, t_exec *e)
{
	e->i = 0;
	e->j = 0;
	e->pids = malloc(sizeof(pid_t) * minishell->howmanycmd);
	e->pfd = create_pipes(minishell);
	e->heredoc_fds = manage_heredocs(minishell);
	signals_ignore();
}

void	restore_std_and_cleanup(t_minishell *minishell,
	t_exec *e)
{
	if (minishell->std_in)
	{
		dup2(minishell->std_in, STDIN_FILENO);
		close(minishell->std_in);
	}
	if (minishell->std_out)
	{
		dup2(minishell->std_out, STDOUT_FILENO);
		close(minishell->std_out);
	}
	if (e->pfd)
		closefds(minishell, e->pfd);
}

void	fork_all_processes(t_minishell *minishell, t_cmd *cmd,
	t_exec *e)
{
	while (e->i < minishell->howmanycmd)
	{
		if (cmd->is_heredoc)
		{
			dup2(e->heredoc_fds[e->j], STDIN_FILENO);
			close(e->heredoc_fds[e->j]);
			e->j++;
		}
		e->pids[e->i] = fork();
		if (e->pids[e->i] == 0)
		{
			if (e->i == 0)
				first_child(minishell, cmd, e);
			else if (e->i == minishell->howmanycmd - 1)
				last_child(minishell, cmd, e);
			else
				execute_command(minishell, cmd, e);
			restore_std_and_cleanup(minishell, e);
			exit(0);
		}
		cmd = cmd->next;
		e->i++;
	}
}

void	wait_all_children(t_minishell *minishell, pid_t *pids)
{
	char	*exit_st;
	int		i;
	int		status;
	int		sign;

	i = 0;
	while (i < minishell->howmanycmd)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sign = WTERMSIG(status);
			minishell->last_exit_status = sign + 128;
		}
		else
			minishell->last_exit_status = 1;
		exit_st = ft_itoa(minishell->last_exit_status);
		set_env(&minishell->env_vars, "?", exit_st);
		free(exit_st);
		i++;
	}
	signals_default();
	free(pids);
}

void	execute_all(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	t_exec	e;

	current_cmd = minishell->cmds;
	minishell->std_out = dup(STDOUT_FILENO);
	minishell->std_in = dup(STDIN_FILENO);
	if (minishell->howmanycmd == 1)
	{
		no_pipes(minishell);
		return ;
	}
	init_execution(minishell, &e);
	fork_all_processes(minishell, current_cmd, &e);
	restore_std_and_cleanup(minishell, &e);
	wait_all_children(minishell, e.pids);
	if (e.heredoc_fds)
	{
		free(e.heredoc_fds);
		e.heredoc_fds = NULL;
	}
	free_pipe_fds(e.pfd, minishell->howmanycmd);
	close(minishell->std_out);
	close(minishell->std_in);
}
