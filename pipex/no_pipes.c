#include "../minishell.h"

void	handle_fork_status(t_minishell *minishell, pid_t pid)
{
	int	status;
	char	*exit_str;

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

void	execute_single_builtin_or_fork(t_minishell *minishell)
{
	char	*exit_str;
	pid_t	pid;

	if (is_builtin(minishell->cmds))
	{
		minishell->last_exit_status = internal_commands(minishell->cmds, minishell);
		exit_str = ft_itoa(minishell->last_exit_status);
		set_env(&minishell->env_vars, "?", exit_str);
		free(exit_str);
	}
	else
	{
		signals_ignore();
		pid = fork();
		if (!pid)
			execute(minishell, minishell->cmds);
		handle_fork_status(minishell, pid);
		signals_default();
	}
}

void	setup_redirections_and_heredoc(t_minishell *minishell)
{
	int	heredoc_fd;

	redirimput(minishell->cmds);
	rediroutput(minishell->cmds);
	if (minishell->cmds->here_doc_delim && minishell->cmds->is_heredoc)
	{
		heredoc_fd = handle_heredoc(minishell,
				minishell->cmds->here_doc_delim, minishell->heredoc_sd);
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
}

void	no_pipes(t_minishell *minishell)
{
	int	stdo;
	int	stdi;

	stdo = dup(STDOUT_FILENO);
	stdi = dup(STDIN_FILENO);
	setup_redirections_and_heredoc(minishell);
	execute_single_builtin_or_fork(minishell);
	dup2(stdo, STDOUT_FILENO);
	dup2(stdi, STDIN_FILENO);
	close(stdo);
	close(stdi);
}

