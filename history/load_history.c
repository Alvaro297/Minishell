# include "../minishell.h"

void load_history(t_minishell *minishell)
{
	int		fd;
	char	*line;
	int		count = 0;
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return;
	while ((line = get_next_line(fd)) != NULL)
	{
		line[strlen(line) - 1] = '\0';
		minishell->history = realloc(minishell->history, (count + 2) * sizeof(char *));
		minishell->history[count] = strdup(line);
		minishell->history[count + 1] = NULL;
		count++;
		free(line);
	}
	close(fd);
}
