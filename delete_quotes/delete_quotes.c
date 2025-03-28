# include "../minishell.h"

int		count_characters(char *array)
{
	size_t			i;
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

char	*delete_quotes_array(t_minishell *minishell, char *array, bool is_not_here_doc)
{
	char		*tmp;
	t_quotes	quotes;
	size_t			i;
	int			j;
	if (is_not_here_doc)
		array = ft_quote_printf(minishell, array);
	quotes.in_double_quote = false;
	quotes.in_single_quote = false;
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (count_characters(array) + 1));
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

char	**delete_quotes_double_array(t_minishell *minishell, char **double_array, bool is_not_here_doc)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char) * ft_strlen(*double_array));
	tmp = double_array;
	while (tmp[i])
	{
		tmp[i] = delete_quotes_array(minishell, tmp[i], is_not_here_doc);
		i++;
	}
	return (tmp);
}

void	delete_quotes(t_minishell *minishell, t_cmd *cmd)
{
	if (cmd->cmd)
		cmd->cmd = delete_quotes_array(minishell, cmd->cmd, true);
	if (cmd->args && ft_strcmp(cmd->cmd, "export") != 0)
		cmd->args = delete_quotes_double_array(minishell, cmd->args, true);
	if (cmd->infile)
		cmd->infile = delete_quotes_array(minishell, cmd->infile, true);
	if (cmd->outfile)
		cmd->outfile = delete_quotes_array(minishell, cmd->outfile, true);
	if (cmd->outfile_array)
		cmd->outfile_array = delete_quotes_double_array(minishell, cmd->outfile_array, true);
	if (cmd->here_doc_delim && cmd->is_heredoc)
		cmd->here_doc_delim = delete_quotes_double_array(minishell, cmd->here_doc_delim, false);
}
