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
	g_signal = 130;
	close(0);
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

static void	process_heredoc_signals(struct sigaction *sa_old,
		struct sigaction *sa_new)
{
	sigaction(SIGINT, NULL, sa_old);
	sa_new->sa_handler = sigint_heredoc_handler;
	memset(&sa_new->sa_mask, 0, sizeof(sa_new->sa_mask));
	sa_new->sa_flags = 0;
	sigaction(SIGINT, sa_new, NULL);
}

static int	process_heredoc_loop(t_minishell *minishell, const char *delimiter,
								int fd, bool heredoc_sd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			write(STDOUT_FILENO, "\n", 1);
			close(fd);
			g_signal = 0;
			return (-2);
		}
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_help(heredoc_sd, minishell, line, fd);
	}
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
	ret = process_heredoc_loop(minishell, delimiter, fd, heredoc_sd);
	close(fd);
	if (ret == -2)
		unlink(tmpfile);
	sigaction(SIGINT, &sa_old, NULL);
	if (ret == -2)
		return (-1);
	return (0);
}
