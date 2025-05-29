/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 21:17:21 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 21:17:21 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_characters(char *array)
{
	size_t		i;
	int			count;
	t_quotes	quotes;

	quotes.in_double_quote = false;
	quotes.in_single_quote = false;
	i = 0;
	count = 0;
	while (array[i])
	{
		if (ft_sd_quote_printf(array, &quotes, &i) == 0)
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	*delete_quotes_core(char *array)
{
	t_quotes	quotes;
	size_t		i;
	int			j;
	char		*tmp;

	quotes.in_double_quote = false;
	quotes.in_single_quote = false;
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (count_characters(array) + 1));
	if (!tmp)
		return (NULL);
	while (array[i])
	{
		if (ft_sd_quote_printf(array, &quotes, &i) == 0)
		{
			tmp[j] = array[i];
			j++;
			i++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*delete_quotes_array(t_minishell *minishell, char *array,
		bool is_not_here_doc, bool is_iofile)
{
	char	*tmp;
	char	*to_free;

	to_free = NULL;
	if (is_not_here_doc)
	{
		to_free = ft_quote_printf(minishell, array, false);
		if (is_iofile)
			free(array);
		array = to_free;
	}
	tmp = delete_quotes_core(array);
	if (to_free)
		free(to_free);
	return (tmp);
}

void	delete_quotes(t_minishell *minishell, t_cmd *cmd)
{
	if (cmd->cmd)
		cmd->cmd = delete_quotes_array(minishell,
				cmd->cmd, true, false);
	if (cmd->infile)
		cmd->infile = delete_quotes_array(minishell,
				cmd->infile, true, true);
	if (cmd->outfile)
		cmd->outfile = delete_quotes_array(minishell,
				cmd->outfile, true, true);
	if (cmd->args)
		cmd->args = delete_quotes_double_array(minishell, cmd->args, true);
	if (cmd->outfile_array)
		cmd->outfile_array = delete_quotes_double_array(minishell,
				cmd->outfile_array, true);
	if (cmd->here_doc_delim && cmd->is_heredoc)
		cmd->here_doc_delim = delete_quotes_double_array(minishell,
				cmd->here_doc_delim, true);
}
