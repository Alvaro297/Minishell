#include "../minishell.h"

static int	get_size(char **input)
{
	int	c;
	int	count;

	c = 0;
	count = 0;
	while (input[c])
	{
		if ((!ft_strncmp(input[c], ">", 1) && ft_strlen(input[c]) == 1)
			|| (!ft_strncmp(input[c], ">>", 2) && ft_strlen(input[c]) == 2))
		{
			if (is_redirected(input[c + 1]))
				break;
			count++;
		}
		c++;
	}
	return (count);
}

char	**get_outfiles(t_minishell *minishell, char **command_splited)
{
	char	**outfile_array;
	int		c;
	int		c1;
	int		size;

	size = get_size(command_splited);
	c1 = 0;
	c = 0;
	if (size == 0)
		return (NULL);
	outfile_array = malloc(sizeof(char *) * (size + 1));
	while (command_splited[c])
	{
		if ((!ft_strncmp(command_splited[c], ">", 1) && ft_strlen(command_splited[c]) == 1)
				|| (!ft_strncmp(command_splited[c], ">>", 2) && ft_strlen(command_splited[c]) == 2))
		{
			if (is_redirected(command_splited[c + 1]) || is_env_var_null(minishell, command_splited[c + 1]))
				break;
			outfile_array[c1] = ft_strdup(command_splited[c + 1]);
			c++;
			c1++;
		}
		c++;
	}
	outfile_array[c1] = NULL;
	return (outfile_array);
}
