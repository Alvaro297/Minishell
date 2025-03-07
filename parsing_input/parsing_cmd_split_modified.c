# include "../minishell.h"

static int	ft_count_words(char *command, bool in_single_quote, bool in_double_quote, int c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (command[i] && command[i] == c)
		i++;
	while (command[i])
	{
		ft_sd_quote_printf(command, &in_single_quote, &in_double_quote, &i);
		if (command[i] == c && !in_single_quote && !in_double_quote)
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
	if (in_single_quote || in_double_quote)
		return (-1);
	return (count);
}

static char	*get_next_word_help(char *start, char **command)
{
	size_t word_len;
	char *word;
	bool in_single_quote;
	bool in_double_quote;

	in_double_quote = false;
	in_single_quote = false;
	word_len = 0;
	word = malloc((*command - start) + 1);
	if (!word)
		return (NULL);
	while (start < *command)
	{
		start = ft_sd_quote_printf_mod3(start, &in_single_quote, &in_double_quote);
		word[word_len++] = *start;
		start++;
	}
	word[word_len] = '\0';
	return (word);
}

static char	*get_next_word(char **command, bool *in_single_quote, bool *in_double_quote)
{
	char	*start;
	char	*word;
	size_t	len;

	len = 0;
	while (**command && (**command == ' ' || **command == '\t' || **command == '\n'))
		(*command)++;
	start = *command;
	while (**command && (!(**command == ' ' || **command == '\t' || **command == '\n') || *in_single_quote || *in_double_quote))
	{
		if (ft_sd_quote_printf_mod2(command, in_single_quote,
				in_double_quote))
			continue;
		(*command)++;
		len++;
	}
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	return (get_next_word_help(start, command));
}

static char	**split_modified_help(char **result, char *command)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (*command)
	{
		result[i] = get_next_word(&command, &in_single_quote, &in_double_quote);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**split_modified(char *command, int c)
{
	int		count_words;
	int		i;
	char	**result;

	count_words = ft_count_words(command, false, false, c);
	if (count_words == -1)
	{
		ft_putstr_fd("Error: unclosed quotes\n", 2);
		return (NULL);
	}
	result = malloc(sizeof(char *) * (count_words + 1));
	if (!result)
		return (NULL);
	return (split_modified_help(result, command));
}
