#include "../minishell.h"

int	ft_count_command_splited(char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
		i++;
	return (i);
}

int	ft_count_newarray(char **command_splited, int i, t_quotes *quotes, int count_total_array)
{
	int	j;

	while (command_splited[i])
	{
		j = 0;
		while (command_splited[i][j])
		{
			ft_sd_quote_printf_mod(command_splited[i], quotes, j);
			if ((command_splited[i][j] == '<' || command_splited[i][j] == '>') &&
				!quotes->in_single_quote && !quotes->in_double_quote)
			{
				if (j != 0 && command_splited[i][j + 1])
					count_total_array += 1;
				if (command_splited[i][j + 1] == command_splited[i][j])
					j++;
				count_total_array += 1;
			}
			j++;
		}
		i++;
	}
	return (count_total_array);
}