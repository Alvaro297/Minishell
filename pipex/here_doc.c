/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:41:05 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:41:07 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_and_append_tmp_file(char *tmp, int final_fd)
{
	int		tmp_fd;
	char	buf[4096];
	ssize_t	n;

	tmp_fd = open(tmp, O_RDONLY);
	if (tmp_fd >= 0)
	{
		n = read(tmp_fd, buf, sizeof(buf));
		while (n > 0)
		{
			write(final_fd, buf, n);
			n = read(tmp_fd, buf, sizeof(buf));
		}
		close(tmp_fd);
	}
	unlink(tmp);
	free(tmp);
}

void	write_tmp_heredocs_to_final(t_minishell *minishell,
	char **delimiters, bool heredoc_sd, int final_fd)
{
	int		i;
	char	*suffix;
	char	*tmp;

	i = 0;
	while (delimiters[i])
	{
		suffix = ft_itoa(i);
		tmp = ft_strjoin(TMP_HEREDOC, suffix);
		free (suffix);
		if (process_heredoc(minishell, delimiters[i], tmp, heredoc_sd) < 0)
		{
			free (tmp);
			return ;
		}
		read_and_append_tmp_file(tmp, final_fd);
		i++;
	}
}

int	handle_heredoc(t_minishell *minishell, char **delimiters, bool heredoc_sd)
{
	char	*final_tmp;
	int		final_fd;
	int		fd;

	final_tmp = ft_strjoin(TMP_HEREDOC, "_final");
	final_fd = open(final_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (final_fd < 0)
	{
		perror("open final heredoc");
		free(final_tmp);
		return (-1);
	}
	write_tmp_heredocs_to_final(minishell, delimiters, heredoc_sd, final_fd);
	close(final_fd);
	fd = open(final_tmp, O_RDONLY);
	unlink(final_tmp);
	free(final_tmp);
	if (fd < 0)
	{
		perror("open final heredoc");
		return (-1);
	}
	return (fd);
}

int	*manage_heredocs(t_minishell *minishell)
{
	t_cmd	*cmd;
	int		i;
	int		*fd;

	cmd = minishell->cmds;
	i = 0;
	fd = malloc(sizeof(int) * minishell->howmanycmd);
	while (cmd)
	{
		if (cmd->is_heredoc)
		{
			fd[i] = handle_heredoc
				(minishell, cmd->here_doc_delim, minishell->heredoc_sd);
			i++;
		}
		cmd = cmd->next;
	}
	cmd = minishell->cmds;
	return (fd);
}
