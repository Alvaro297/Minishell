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

char	*delete_quotes_array(t_minishell *minishell, char *array, bool is_not_here_doc, bool is_iofile)
{
	char		*tmp;
	char		*to_free = NULL;
	t_quotes	quotes;
	size_t		i;
	int			j;

	if (is_not_here_doc)
	{
		to_free = ft_quote_printf(minishell, array);
		if (is_iofile)
			free(array);
		array = to_free;
	}
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
	if (to_free)
		free(to_free);
	return (tmp);
}

char	**delete_quotes_double_array(t_minishell *minishell, char **double_array, bool is_not_here_doc)
{
	int		i;
	int		count;
	char	**tmp;

	if (double_array == NULL)
		return (NULL);
	count = 0;
	while (double_array[count])
		count++;
	tmp = malloc(sizeof(char *) * (count + 1));
	if (tmp == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (double_array[i])
	{
		char *old_str = double_array[i];
		tmp[i] = delete_quotes_array(minishell, old_str, is_not_here_doc, false);
		free(old_str);
		i++;
	}
	tmp[i] = NULL;
	free(double_array);
	return (tmp);
}

void	delete_quotes(t_minishell *minishell, t_cmd *cmd)
{
	if (cmd->cmd)
		cmd->cmd = delete_quotes_array(minishell, cmd->cmd, true, false);
	if (cmd->infile)
		cmd->infile = delete_quotes_array(minishell, cmd->infile, true, true);
	if (cmd->outfile)
		cmd->outfile = delete_quotes_array(minishell, cmd->outfile, true, true);
	if (cmd->args)
		cmd->args = delete_quotes_double_array(minishell, cmd->args, true);
	if (cmd->outfile_array)
		cmd->outfile_array = delete_quotes_double_array(minishell, cmd->outfile_array, true);
}
