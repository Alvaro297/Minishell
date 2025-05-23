# include "../minishell.h"

static int ft_count_words(char *command, t_quotes *quotes, int c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (command[i] && command[i] == c)
		i++;
	while (command[i])
	{
		ft_sd_quote_printf_mod(command, quotes, i);
		if (command[i] == c && !quotes->in_single_quote && !quotes->in_double_quote)
		{
			count++;
			while (command[i] == c)
				i++;
		}
		else
			i++;
	}
	if (i > 0 && command[i - 1] != c)
		count++;
	return (count);
}

static char *get_next_word_help(char *start, char **command, t_quotes *quotes)
{
	size_t word_len;
	char *word;

	word_len = 0;
	word = malloc((*command - start) + 1);
	if (!word)
		return (NULL);
	while (start < *command)
	{
		ft_sd_quote_printf_mod3(start, quotes);
		word[word_len++] = *start;
		start++;
	}
	word[word_len] = '\0';
	return (word);
}

static char *get_next_word(char **command, t_quotes *quotes)
{
	char	*start;
	size_t	len;

	len = 0;
	while (**command && (**command == ' ' || **command == '\t' || **command == '\n'))
		(*command)++;
	start = *command;
	while (**command && (!(**command == ' ' || **command == '\t' || **command == '\n') || quotes->in_single_quote || quotes->in_double_quote))
	{
		ft_sd_quote_printf_mod3(*command, quotes);
		(*command)++;
		len++;
	}
	if (len != 0)
		return (get_next_word_help(start, command, quotes));
	return (NULL);
}

static char **split_modified_help(char **result, char *command)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	while (*command)
	{
		result[i] = get_next_word(&command, &quotes);
		if (!result[i])
			break ;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**split_modified(char *command, int c)
{
	int		count_words;
	char	**result;
	t_quotes	quotes;

	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	count_words = ft_count_words(command, &quotes, c);
	result = malloc(sizeof(char *) * (count_words + 1));
	if (!result)
		return (NULL);
	return (split_modified_help(result, command));
}
