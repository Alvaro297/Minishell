# include "../minishell.h"

void	load_history(t_minishell *minishell)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	if (access(HISTORY_FILE, F_OK) == -1)
		return ;	
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return;
	while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strlen(line) - 1] = '\0';
		minishell->history = ft_realloc(minishell->history, (count + 2) * sizeof(char *));
		minishell->history[count] = ft_strdup(line);
		minishell->history[count + 1] = NULL;
		count++;
		free(line);
	}
	close(fd);
}

void	add_to_history(t_minishell *minishell, char *input)
{
	int		fd;
	int		i;

	i = 0;
	while (minishell->history && minishell->history[i])
		i++;
	minishell->history = ft_realloc(minishell->history, (i + 2) * sizeof(char *));
	minishell->history[i] = ft_strdup(input);
	minishell->history[i + 1] = NULL;
	fd = open(HISTORY_FILE, O_WRONLY | O_APPEND | O_CREAT);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (write(fd, input, strlen(input)) == -1 || write(fd, "\n", 1) == -1)
	{
		perror("write");
		close(fd);
		return ;
	}
	close(fd); 
}
