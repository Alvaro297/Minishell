#include "../../minishell.h"

static char	*handle_quotes_in_echo_while(char *first_quote_pos, char *input_mini, int c)
{
	char	*input;
	char	*new_input;
	char	*additional_input;

	input = input_mini;
	while ((first_quote_pos && ft_strchr(first_quote_pos + 1, c) == NULL))
	{
		additional_input = readline("> ");
		if (additional_input == NULL)
		{
			free(input);
			free(additional_input);
			return NULL;
		}
		new_input = ft_strjoin(input, "\n");
		new_input = ft_strjoin(new_input, additional_input);
		free(input);
		free(additional_input);
		input = new_input;
		first_quote_pos = ft_strchr(input, c);
	}
	return (input);
}

static bool	handle_quotes_in_echo(t_minishell *minishell)
{
	char	*single_quote_pos;
	char	*double_quote_pos;
	char	*first_quote_pos;
	bool	is_single_quote;

	single_quote_pos = ft_strchr(minishell->input, '\'');
	double_quote_pos = ft_strchr(minishell->input, '"');
	if (single_quote_pos && double_quote_pos)
		first_quote_pos = (single_quote_pos < double_quote_pos) ? single_quote_pos : double_quote_pos;
	else if (single_quote_pos)
		first_quote_pos = single_quote_pos;
	else if (double_quote_pos)
		first_quote_pos = double_quote_pos;
	else 
		first_quote_pos = NULL;
	if (first_quote_pos == single_quote_pos)
		is_single_quote = true;
	else
		is_single_quote = false;
	if (is_single_quote && first_quote_pos)
		minishell->input = handle_quotes_in_echo_while(minishell->input, '\'');
	else if (!is_single_quote && first_quote_pos)
		minishell->input = handle_quotes_in_echo_while(minishell->input, '"');
	return (first_quote_pos != NULL);
}

int	handle_echo(t_minishell *minishell, char **envp)
{
	int		i;
	int		newline;
	bool	quotes;

	i = 1;
	newline = 1;
	//quotes = handle_quotes_in_echo(minishell);
	//if (quotes)
		//minishell->parsed_input = ft_split(minishell->input, ' ');
	if (minishell->input != NULL &&
			ft_strncmp(minishell->parsed_input[i], "-n", 2) == 0 &&
			ft_strlen(minishell->parsed_input[i]) == 2)
	{
		i++;
		newline = 0;
	}
	while (minishell->parsed_input[i] != NULL)
		printf("%s ", minishell->parsed_input[i++]);
	if (newline)
		printf("\n");
	return (1);
}
