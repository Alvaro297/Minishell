# include "../minishell.h"



static int	ft_add_token(char *cmd, char **tokens, int *k, int *j)
{
	if (cmd[*j] == cmd[*j + 1])
	{
		tokens[*k] = ft_strndup(&cmd[*j], 2);
		(*j)++;
	}
	else
		tokens[*k] = ft_strndup(&cmd[*j], 1);
	(*k)++;
	(*j)++;
	return (*j);
}

static int	ft_handle_redirection(char *cmd, char **tokens, int *k, t_quotes *quotes)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	while (cmd[j])
	{
		ft_sd_quote_printf_mod(cmd, quotes, j);
		if ((cmd[j] == '<' || cmd[j] == '>') && 
			!quotes->in_single_quote && !quotes->in_double_quote)
		{
			if (j > start)
				tokens[(*k)++] = ft_strndup(&cmd[start], j - start);
			start = ft_add_token(cmd, tokens, k, &j);
		}
		else
			j++;
	}
	if (j > start)
		tokens[(*k)++] = ft_strndup(&cmd[start], j - start);
	return (*k);
}

static char	**process_redirection_help(char **cmd_split, char **tokens)
{
	int		i;
	int		k;
	t_quotes	quotes;

	i = 0;
	k = 0;
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	while (cmd_split[i])
	{
		ft_handle_redirection(cmd_split[i], tokens, &k, &quotes);
		i++;
	}
	tokens[k] = NULL;
	return (tokens);
}


char	**process_redirection(char **command_splited)
{
	int		count_newarray;
	char	**command_splited_token;
	t_quotes	quotes;

	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	count_newarray = ft_count_command_splited(command_splited);
	count_newarray = ft_count_newarray(command_splited, 0, &quotes, count_newarray);
	command_splited_token = malloc(sizeof(char *) * (count_newarray + 1));
	if (!command_splited_token)
	{
		perror("malloc");
		return (NULL);
	}
	return (process_redirection_help(command_splited, command_splited_token));
}
