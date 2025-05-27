/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 13:46:30 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-27 13:46:30 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_heredoc(char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if (ft_strcmp(command_splited[i], "<<") == 0)
			return (true);
		i++;
	}
	return (false);
}

int	ft_count_heredocs(char **command_splited)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (command_splited[i])
	{
		if (ft_strcmp(command_splited[i], "<<") == 0)
		{
			if (command_splited[i + 1]
				&& !is_redirected(command_splited[i + 1]))
			{
				i++;
				count++;
			}
			else
				return (-1);
		}
		i++;
	}
	return (count);
}

static char	**free_and_null(char **heredocs_delim,
	char **split_input_inic)
{
	free_double_array((void **)heredocs_delim);
	free_double_array((void **)split_input_inic);
	return (NULL);
}

static char	**here_doc_delim_help(char **heredocs_delim,
	char **split_input_inic, int count)
{
	int	i;

	i = 0;
	while (split_input_inic[i])
	{
		if (ft_strncmp(split_input_inic[i], "<<", 2) == 0)
		{
			if (split_input_inic[i + 1]
				&& !is_redirected(split_input_inic[i + 1]))
			{
				i++;
				heredocs_delim[count] = ft_strdup(split_input_inic[i]);
				if (!heredocs_delim[count])
					return (free_and_null(heredocs_delim, split_input_inic));
				count++;
			}
			else
				return (free_and_null(heredocs_delim, split_input_inic));
		}
		i++;
	}
	heredocs_delim[count] = NULL;
	free_double_array((void **)split_input_inic);
	return (heredocs_delim);
}

char	**here_doc_delim(char *input)
{
	char		**heredocs_delim;
	char		**split_input_inic;
	int			count_heredocs;

	split_input_inic = split_modified(input, ' ');
	split_input_inic = process_redirection(split_input_inic);
	count_heredocs = ft_count_heredocs(split_input_inic);
	heredocs_delim = malloc(sizeof(char *) * (count_heredocs + 1));
	if (!heredocs_delim)
	{
		free_double_array((void **)split_input_inic);
		return (NULL);
	}
	return (here_doc_delim_help(heredocs_delim, split_input_inic, 0));
}
