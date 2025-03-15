#include "minishell.h"

bool check_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;
	int	c;

	c = 0;
	while (input[c] != '\0')
	{
		if (input[i] == '\'')
			single_quotes++;
		else if (input[i] == '"')
			double_quotes++;
		c++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

bool	check_redir(char *input)
{
	int	c;

	c = 0;
	if (input[0] == '>' || input[0] == '<')
		return (false);
	while (input[c] != '\0')
	{
		if ((input[c] == '>' || input[c] == '<') &&
				(input[c + 1] == '<'))
            return (false);
		if (input[i] == '<' && input[i+1] == '>')
            return false;
	}
	return (true);
}

bool	check_pipes(char *input)
{
	int	c;

	c = 0;
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
        return (false);
	while (input[c] != '\0')
	{
		 if (input[c] == '|' && input[c+1] == '|')
            return (false);
	}
	return (true);
}

bool	check_syntax(char *input)
{
	if (!check_quotes(input))
	{
        printf("Error: Comillas no balanceadas.\n");
        return (false);
  }
  if (!check_redir(input))
	{
        printf("Error: Sintaxis incorrecta en redirección.\n");
        return (false);
  }
  if (!check_pipes(input))
	{
        printf("Error: Sintaxis incorrecta en pipes.\n");
        return (false);
  }
	return (true);
}
