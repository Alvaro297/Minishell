/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:44:37 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:44:55 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

static void	process_heredoc_help(bool heredoc_sd,
		t_minishell *minishell, char *line, int fd)
{
	char	*expanded;

	expanded = NULL;
	if (!heredoc_sd)
	{
		expanded = ft_quote_printf_here_doc(minishell, line);
		dprintf(fd, "%s\n", expanded);
	}
	else
		dprintf(fd, "%s\n", line);
	if (expanded)
		free(expanded);
	free(line);
}

int	process_heredoc(t_minishell *minishell,
		const char *delimiter, char *tmpfile, bool heredoc_sd)
{
	char	*line;
	int		fd;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	signal(SIGINT, sigint_heredoc_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_help(heredoc_sd, minishell, line, fd);
	}
	close(fd);
	return (0);
}
