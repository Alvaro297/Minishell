#include "../minishell.h"

void sigint_heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

static int process_heredoc(const char *delimiter, char *tmpfile)
{
	char *line;
	int fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	signal(SIGINT, sigint_heredoc_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		dprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	return 0;
}

int handle_heredoc(char **delimiters)
{
	char	*final_tmp;
	int		final_fd;
	int		i;
	char *suffix; 
	char *tmp;

	final_tmp = ft_strjoin(TMP_HEREDOC, "_final");
	final_fd = open(final_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (final_fd < 0)
	{
		perror("open final heredoc");
		free(final_tmp);
		return -1;
	}
	i = 0;
	while (delimiters[i])
	{
		suffix = ft_itoa(i);
		tmp = ft_strjoin(TMP_HEREDOC, suffix);
		free(suffix);

		if (process_heredoc(delimiters[i], tmp) < 0)
		{
			free(tmp);
			continue;
		}
		int tmp_fd = open(tmp, O_RDONLY);
		if (tmp_fd >= 0)
		{
			char buf[4096];
			ssize_t n;
			while ((n = read(tmp_fd, buf, sizeof(buf))) > 0)
				write(final_fd, buf, n);
			close(tmp_fd);
		}
		unlink(tmp);
		free(tmp);
		i++;
	}
	close(final_fd);
	int fd = open(final_tmp, O_RDONLY);
	unlink(final_tmp);
	free(final_tmp);
	if (fd < 0)
	{
		perror("open final heredoc");
		return -1;
	}
	return fd;
}

int	*manage_heredocs(t_minishell *minishell)
{
	t_cmd *cmd;
	int	i;
	int	*fd;
	//int	fdopen;

	cmd = minishell->cmds;
	i = 0;
	fd = malloc(sizeof(int) * minishell->howmanycmd);
	while (cmd)
	{
		if (cmd->is_heredoc)
		{
			fd[i] = handle_heredoc(cmd->here_doc_delim);
			i++;
		}
		cmd = cmd->next;
	}
	cmd = minishell->cmds;
	return (fd);
}
