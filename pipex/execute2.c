/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:33:26 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:33:28 by paperez-         ###   ########.fr       */
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

void	fork_all_processes(t_minishell *minishell, t_cmd *cmd,
	t_exec *e, int std_out)
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
				first_child(minishell, cmd, e->pfd);
			else if (e->i == minishell->howmanycmd - 1)
				last_child(minishell, cmd, e->pfd, std_out);
			else
				execute_command(minishell, cmd, e->pfd, e->i);
			exit(0);
		}
		cmd = cmd->next;
		e->i++;
	}
}

void	restore_std_and_cleanup(t_minishell *minishell,
	t_exec *e, int std_in)
{
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	free(e->heredoc_fds);
	closefds(minishell, e->pfd);
}

void	wait_all_children(t_minishell *minishell, pid_t *pids)
{
	int	i;
	int	status;
	int	sign;

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
		set_env(&minishell->env_vars, "?",
			ft_itoa(minishell->last_exit_status));
		i++;
	}
	manage_signals();
	free(pids);
}

void	execute_all(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	int		std_out;
	int		std_in;
	t_exec	e;

	current_cmd = minishell->cmds;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (minishell->howmanycmd == 1)
	{
		no_pipes(minishell);
		return ;
	}
	init_execution(minishell, &e);
	fork_all_processes(minishell, current_cmd, &e, std_out);
	restore_std_and_cleanup(minishell, &e, std_in);
	wait_all_children(minishell, e.pids);
	free_pipe_fds(e.pfd, minishell->howmanycmd);
}
