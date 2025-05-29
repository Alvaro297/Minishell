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

int	process_heredoc(t_minishell *minishell,
	const char *delimiter, char *tmpfile, bool heredoc_sd)
{
	char				*line;
	int					fd;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	sigaction(SIGINT, NULL, &sa_old);
	sa_new.sa_handler = sigint_heredoc_handler;
	memset(&sa_new.sa_mask, 0, sizeof(sa_new.sa_mask));
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, NULL);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			write(STDOUT_FILENO, "\n", 1); // Solo un salto de línea
			close(fd);
			unlink(tmpfile);
			g_signal = 0;
			sigaction(SIGINT, &sa_old, NULL); // Restaurar handler original
			return (-1);
		}
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_help(heredoc_sd, minishell, line, fd);
	}

	close(fd);
	sigaction(SIGINT, &sa_old, NULL); // Restaurar handler original
	return (0);
}
