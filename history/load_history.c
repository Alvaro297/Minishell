/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:06 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:06 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

static int	history_realloc_and_store(t_minishell *minishell, char *line, int count)
{
	int		old_count;
	char	**new_history;

	old_count = 0;
	if (minishell->history)
		while (minishell->history[old_count])
			old_count++;
	new_history = ft_realloc(
		minishell->history,
		(old_count + 1) * sizeof(char *),
		(count + 2) * sizeof(char *)
	);
	if (!new_history)
		return (0);
	minishell->history = new_history;
	minishell->history[count] = ft_strdup(line);
	if (!minishell->history[count])
		return (0);
	minishell->history[count + 1] = NULL;
	return (1);
}

static void	load_history_line(t_minishell *minishell, char *line, int *count)
{
	line[ft_strlen(line) - 1] = '\0';
	add_history(line);
	if (!history_realloc_and_store(minishell, line, *count))
	{
		free(line);
		return ;
	}
	(*count)++;
	free(line);
}

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
		load_history_line(minishell, line, &count);
	close(fd);
}

void	add_to_history(t_minishell *minishell, char *input)
{
	int		fd;
	int		i;
	char	**new_history;

	i = 0;
	while (minishell->history && minishell->history[i])
		i++;
	new_history = ft_realloc(
		minishell->history,
		(i + 1) * sizeof(char *),
		(i + 2) * sizeof(char *)
	);
	if (!new_history)
	{
		perror("ft_realloc");
		return;
	}
	minishell->history = new_history;
	minishell->history[i] = ft_strdup(input);
	if (!minishell->history[i])
	{
		perror("ft_strdup");
		return;
	}
	minishell->history[i + 1] = NULL;
	fd = open(HISTORY_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (write(fd, input, ft_strlen(input)) == -1 || write(fd, "\n", 1) == -1)
	{
		perror("write");
		close(fd);
		return ;
	}
	close(fd); 
}
