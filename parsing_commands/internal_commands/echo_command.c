#include "../../minishell.h"

int	handle_echo(t_minishell *minishell)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (minishell->input != NULL &&
			ft_strncmp(minishell->parsed_input[i], "-n", 2) == 0 &&
			ft_strlen(minishell->parsed_input[i]) == 2)
	{
		i++;
		newline = 0;
	}
	while (minishell->parsed_input[i] != NULL)
	{
		printf("%s", minishell->parsed_input[i]);
		if (minishell->parsed_input[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}
