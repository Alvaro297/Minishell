#include "../minishell.h"

static int	get_children(t_minishell *minishell)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(minishell->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == minishell->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_children(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmd;
	while (minishell->pid != 0 && cmd)
	{
		minishell->pid = fork();
		if (minishell->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (minishell->pid == 0)
			execute_command(minishell, cmd);
		cmd = cmd->next;
	}
	return (get_children(minishell));
}



static int	prep_for_exec(t_minishell *minishell)
{
	if (!minishell || !minishell->cmd)
			return (EXIT_SUCCESS);
	if (!minishell->cmd->command)
	{
		if (minishell->cmd->io_fds
			&& !check_infile_outfile(minishell->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(minishell))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	execute(t_minishell *minishell)
{
	int	ret;

	ret = prep_for_exec(minishell);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!minishell->cmd->pipe_output && !minishell->cmd->prev
		&& check_infile_outfile(minishell->cmd->io_fds))
	{
		redirect_io(minishell->cmd->io_fds);
		ret = execute_builtin(minishell, minishell->cmd);
		restore_io(minishell->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(minishell));
}
