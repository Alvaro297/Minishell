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
	char		*to_free = NULL;
	t_quotes	quotes;
	size_t		i;
	int			j;

	if (is_not_here_doc)
	{
		to_free = ft_quote_printf(minishell, array);
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
		tmp[i] = delete_quotes_array(minishell, double_array[i], is_not_here_doc);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

static void	delete_quotes_arrays(t_minishell *minishell, t_cmd *cmd)
{
	char	**old_arr;

	if (cmd->args) {
		old_arr = cmd->args;
		cmd->args = delete_quotes_double_array(minishell, old_arr, true);
		free_double_array((void **)old_arr);
	}
	if (cmd->outfile_array) {
		old_arr = cmd->outfile_array;
		cmd->outfile_array = delete_quotes_double_array(minishell, old_arr, true);
		free_double_array((void **)old_arr);
	}
	if (cmd->here_doc_delim && cmd->is_heredoc) {
		old_arr = cmd->here_doc_delim;
		cmd->here_doc_delim = delete_quotes_double_array(minishell, old_arr, false);
		free_double_array((void **)old_arr);
	}
}

void	delete_quotes(t_minishell *minishell, t_cmd *cmd)
{
	char	*old_str;

	if (cmd->cmd) {
		old_str = cmd->cmd;
		cmd->cmd = delete_quotes_array(minishell, old_str, true);
		free(old_str);
	}
	if (cmd->infile) {
		old_str = cmd->infile;
		cmd->infile = delete_quotes_array(minishell, old_str, true);
		free(old_str);
	}
	if (cmd->outfile) {
		old_str = cmd->outfile;
		cmd->outfile = delete_quotes_array(minishell, old_str, true);
		free(old_str);
	}
	delete_quotes_arrays(minishell, cmd);
}
