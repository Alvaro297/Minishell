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

char	*delete_quotes_array(char *array)
{
	char		*tmp;
	t_quotes	quotes;
	size_t			i;
	int			j;

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

char	**delete_quotes_double_array(char **double_array)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = double_array;
	while (tmp[i])
	{
		tmp[i] = delete_quotes_array(tmp[i]);
		i++;
	}
	return (tmp);
}

void	delete_quotes(t_cmd *cmd)
{
	cmd->cmd = delete_quotes_array(cmd->cmd);
	cmd->args = delete_quotes_double_array(cmd->args);
	cmd->infile = delete_quotes_array(cmd->infile);
	cmd->outfile = delete_quotes_array(cmd->outfile);
	cmd->outfile_array = delete_quotes_double_array(cmd->outfile_array);
}