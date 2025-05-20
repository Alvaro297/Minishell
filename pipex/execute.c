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

void logadd(const char *log_entry) {
	// Abrir el archivo en modo de anexado ("a")
	FILE *file = fopen("minishell.log", "a");
	if (file == NULL) {
		perror("No se pudo abrir el archivo");
		return;
	}
	// Escribir la entrada de log en una nueva línea
	fprintf(file, "%s\n", log_entry);
	// Cerrar el archivo
	fclose(file);
}

void	last_child(t_minishell *minishell, t_cmd *cmd, int **pfd, int std_out)
{
	//int	fd;
	logadd("ESTOY EN EL ULTIMO HIJO\n");
	if (cmd->cmd)
		logadd(cmd->cmd);
	else
		logadd("NO HAY CMD");
	//fd = open_f(cmd->outfile, 1);
	if (cmd->infile)
		redirimput(cmd);
	else
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
//	int	fd;

	logadd("ESTOY EN EL PRIMER HIJO:\n");
	if (cmd->cmd)
		logadd(cmd->cmd);
	else
		logadd("NO HAY CMD");
/*	if (cmd->output != NULL)
	{
		fd = open_f();
	}*/
	//TODO implementar los heredocs
	//dup2(pfd[0][0], STDIN_FILENO);
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

void	first_cmd_builtin(t_minishell *minishell, t_cmd *cmd, int **pfd)
{
	logadd("ESTOY EN EL PRIMER HIJO:\n");
	if (cmd->cmd)
		logadd(cmd->cmd);
	else
		logadd("NO HAY CMD");
	if (ft_strcmp(minishell->cmds->cmd, "cd") == 0 || 
			ft_strcmp(minishell->cmds->cmd, "exit") == 0 || 
			ft_strcmp(minishell->cmds->cmd, "unset") == 0 ||
				ft_strcmp(minishell->cmds->cmd, "export") == 0)
				{
					minishell->cmds = minishell->cmds->next;
					minishell->howmanycmd = minishell->howmanycmd -1;
					printf("ESTE ES EL · CMD: %s\n", minishell->cmds->next->cmd);
					execute_all(minishell);
					return ;
				}
	//TODO implementar los heredocs
	//dup2(pfd[0][0], STDIN_FILENO);
	dup2(pfd[0][1], STDOUT_FILENO);
	//closefds(minishell, pfd);
	close(pfd[0][1]);
	execute(minishell, cmd);
}

void	execute_command(t_minishell *minishell, t_cmd *cmd, int ** pfd, int i)
{
	logadd("ESTOY EN EL n HIJO:\n");
	if (cmd->infile)
		redirimput(cmd);
	else
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

void	executebuiltin(t_minishell *minishell)
{
	int	**pfd;
	int	i;
	pid_t *pids;
	t_cmd	*current_cmd;
	int	std_out;
	
	i = 1;
	current_cmd = minishell->cmds;
	std_out = dup(STDOUT_FILENO);
	pids = malloc(sizeof(pid_t) * (minishell->howmanycmd - 1));
	pfd = create_pipes(minishell);
	first_cmd_builtin(minishell, current_cmd, pfd);
	if (minishell->cmds->cmd == NULL)
		return ;
	close(pfd[0][1]);
	current_cmd = current_cmd->next;
	while (i < minishell->howmanycmd)
	{
		logadd("ESTOY EN LA N EJECUCIÖN:\n");
		pids[i - 1] = fork();
		if (pids[i - 1] == 0)
		{
			if (i == minishell->howmanycmd - 1)
				last_child(minishell, current_cmd, pfd, std_out);
			else
				execute_command(minishell, current_cmd, pfd, i);
		}
		current_cmd = current_cmd->next;
		close(pfd[i - 1][0]);
		i++;
	}
	closefds(minishell, pfd);
	i = 0;
	while (i < minishell->howmanycmd - 1)//TODO hacer una funcion que se quede con el primer codigo de error si los hay.
	{
		logadd("EN EL PADRE ESPERANDO\n");
		waitpid(pids[i], &minishell->last_exit_status, 0);
		i++;
	}
}

void	execute_all(t_minishell *minishell)
{
	int	**pfd;
	int	i;
	pid_t *pids;
	t_cmd	*current_cmd;
	int	std_out;
	int	heredoc_fd;

	current_cmd = minishell->cmds;
	std_out = dup(STDOUT_FILENO);
	if (minishell->howmanycmd == 1)
	{
		no_pipes(minishell);
		return ;
	}
	/*if (is_builtin(minishell->cmds))
	{
		executebuiltin(minishell);
		return ;
	}*/
	i = 0;
	pids = malloc(sizeof(pid_t) * minishell->howmanycmd);
	pfd = create_pipes(minishell);
	while (i < minishell->howmanycmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (current_cmd->here_doc_delim && current_cmd->here_doc_delim[0])
			{
				heredoc_fd = handle_heredoc(current_cmd->here_doc_delim);
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
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
	closefds(minishell, pfd);
	i = 0;
	while (i < minishell->howmanycmd)//TODO hacer una funcion que se quede con el primer codigo de error si los hay.
	{
		logadd("EN EL PADRE ESPERANDO\n");
		waitpid(pids[i], &minishell->last_exit_status, 0);
		i++;
	}
	free(pids);
	i = 0;
	while (i < minishell->howmanycmd - 1)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}
