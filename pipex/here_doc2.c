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

static void	process_heredoc_help(bool heredoc_sd,
		t_minishell *minishell, char *line, int fd)
{
	char	*expanded;

	expanded = NULL;
	if (!heredoc_sd)
	{
		expanded = ft_quote_printf_here_doc(minishell, line);
		write(fd, expanded, strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
}

static int	process_heredoc_loop(t_minishell *minishell, const char *delimiter,
								int fd, bool heredoc_sd)
{
	char	*line;

	rl_event_hook = heredoc_event_hook;
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(line);
			close(fd);
			rl_event_hook = NULL;
			return (-2);
		}
		if (!line || ft_strcmp(line, (char *) delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_help(heredoc_sd, minishell, line, fd);
	}
	close(fd);
	rl_event_hook = NULL;
	return (0);
}

int	process_heredoc(t_minishell *minishell,
	const char *delimiter, char *tmpfile, bool heredoc_sd)
{
	int					fd;
	struct sigaction	sa_old;
	struct sigaction	sa_new;
	int					ret;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	process_heredoc_signals(&sa_old, &sa_new);
	if (g_signal == 130)
		ret = -2;
	else
		ret = process_heredoc_loop(minishell, delimiter, fd, heredoc_sd);
	if (ret == -2)
		unlink(tmpfile);
	sigaction(SIGINT, &sa_old, NULL);
	if (ret == -2)
		return (-1);
	return (0);
}
