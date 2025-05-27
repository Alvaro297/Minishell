#include "../minishell.h"

void	closefds(t_minishell *minishell, int **fd)
{
	int	i;

	i = 0;
	while (i < minishell->howmanycmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	last_child(t_minishell *minishell, t_cmd *cmd, int **pfd, int std_out)
{
	if (cmd->infile && !cmd->is_heredoc)
		redirimput(cmd);
	else if (!cmd->is_heredoc)
		dup2(pfd[minishell->howmanycmd - 2][0], STDIN_FILENO);
	if (cmd->outfile)
		rediroutput(cmd);
	else
	{
		dup2(std_out, STDOUT_FILENO);
		close(std_out);
	}
	closefds(minishell, pfd);
	execute(minishell, cmd);
}

void	first_child(t_minishell *minishell, t_cmd *cmd, int **pfd)
{
	if (cmd->infile)
		redirimput(cmd);
	if (cmd->outfile)
		rediroutput(cmd);
	else
		dup2(pfd[0][1], STDOUT_FILENO);
	closefds(minishell, pfd);
	//close(pfd[0][1]);
	execute(minishell, cmd);
}

void	execute_command(t_minishell *minishell, t_cmd *cmd, int ** pfd, int i)
{
	if (cmd->infile && !cmd->is_heredoc)
		redirimput(cmd);
	else if (!cmd->is_heredoc)
		dup2(pfd[i - 1][0], STDIN_FILENO);
	if (cmd->outfile)
		rediroutput(cmd);
	else
		dup2(pfd[i][1], STDOUT_FILENO);
	closefds(minishell, pfd);
	execute(minishell, cmd);
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
			return NULL;
		}
		i++;
	}
	return (fd);
}
/*
void	execute_all(t_minishell *minishell)
{
	int	**pfd;
	int	i;
	pid_t *pids;
	t_cmd	*current_cmd;
	int	std_out;
	int	std_in;
	int	*heredoc_fds;
	int	j;
	int	status;

	current_cmd = minishell->cmds;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (minishell->howmanycmd == 1)
	{
		no_pipes(minishell);
		return ;
	}
	i = 0;
	j = 0;
	pids = malloc(sizeof(pid_t) * minishell->howmanycmd);
	pfd = create_pipes(minishell);
	heredoc_fds = manage_heredocs(minishell);
	signals_ignore();
	while (i < minishell->howmanycmd)
	{
		if (current_cmd->is_heredoc)
		{
			dup2(heredoc_fds[j], STDIN_FILENO);
			close(heredoc_fds[j]);
			j++;
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				first_child(minishell, current_cmd, pfd);
			else if (i == minishell->howmanycmd - 1)
				last_child(minishell, current_cmd, pfd, std_out);
			else
				execute_command(minishell, current_cmd, pfd, i);
		}
		if (pids[i] == 0)
			exit (0);
		current_cmd = current_cmd->next;
		i++;
	}
	dup2(std_in, STDIN_FILENO);
	close (std_in);
	free (heredoc_fds);
	closefds(minishell, pfd);
	i = 0;
	while (i < minishell->howmanycmd)	
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->last_exit_status = WTERMSIG(status) + 128;
		else
			minishell->last_exit_status = 1;
		set_env(&minishell->env_vars, "?",
			ft_itoa(minishell->last_exit_status));
		i++;
	}
	signals_default();
	free(pids);
	i = 0;
	while (i < minishell->howmanycmd - 1)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}*/
