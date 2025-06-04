/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:12:42 by paperez-          #+#    #+#             */
/*   Updated: 2025/06/03 21:11:54 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	handle_fork_status(t_minishell *minishell, pid_t pid)
{
	char	*exit_str;
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->last_exit_status = WTERMSIG(status) + 128;
	else
		minishell->last_exit_status = 1;
	exit_str = ft_itoa(minishell->last_exit_status);
	set_env(&minishell->env_vars, "?", exit_str);
	free(exit_str);
}
*/
void	handle_fork_status(t_minishell *minishell, pid_t pid)
{
	char	*exit_str;
	int		status;
	int		exit_code;
	int		signo;

	exit_code = 0;
	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		exit_code = signo + 128;
	}
	else
		exit_code = 1;
	minishell->last_exit_status = exit_code;
	exit_str = ft_itoa(exit_code);
	set_env(&minishell->env_vars, "?", exit_str);
	free(exit_str);
}

void	execute_single_builtin_or_fork(t_minishell *minishell)
{
	char	*exit_str;
	pid_t	pid;

	if (is_builtin(minishell->cmds))
	{
		minishell->last_exit_status
			= internal_commands(minishell->cmds, minishell);
		exit_str = ft_itoa(minishell->last_exit_status);
		set_env(&minishell->env_vars, "?", exit_str);
		free(exit_str);
	}
	else
	{
		signals_ignore();
		pid = fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute(minishell, minishell->cmds);
		}
		handle_fork_status(minishell, pid);
		signals_default();
	}
}

static int	setup_redirections_and_heredoc(t_minishell *minishell)
{
	int	heredoc_fd;
	int	all_ok;

	all_ok = true;
	if (!minishell->cmds->is_heredoc)
		all_ok = redirimput(minishell->cmds);
	if (minishell->cmds->here_doc_delim && minishell->cmds->is_heredoc)
	{
		heredoc_fd = handle_heredoc(minishell,
				minishell->cmds->here_doc_delim, minishell->heredoc_sd);
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	if (all_ok)
		all_ok = rediroutput(minishell->cmds);
	return (all_ok);
}

void	no_pipes(t_minishell *minishell)
{
	bool	fds_ok;
	char	*exit_status;

	exit_status = NULL;
	fds_ok = setup_redirections_and_heredoc(minishell);
	if (fds_ok)
		execute_single_builtin_or_fork(minishell);
	else
	{
		exit_status = ft_itoa(1);
		set_env(&minishell->env_vars, "?", exit_status);
		free (exit_status);
	}
	dup2(minishell->std_out, STDOUT_FILENO);
	dup2(minishell->std_in, STDIN_FILENO);
	close(minishell->std_out);
	close(minishell->std_in);
}
