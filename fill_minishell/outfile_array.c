#include "../minishell.h"

int	get_size(char **input)
{
	int	c;
	int	count;

	c = 0;
	count = 0;
	while (input[c])
	{
		if (!ft_strncmp(input[c], "<", 1) && ft_strlen(input[c] = 1))
			count++;
		c+;
	}
	return (count);
}

char	**get_outfiles(char **command_splited)
{
	char	**outfile_array;
	int	c;
	int	c1;

	c1 = 0;
	c = 0;
	outfile_array = malloc(sizeof(char *) * get_size(command_splited));
	while (command_splited[c])
	{
		if (!ft_strncmp(command_splited[c], "<", 1) && ft_strlen(input[c] = 1))
		{
			outfile_array[c1] = command_splited[c + 1];
			c++;
			c1++;
		}
		c++;
	}
	return (outfile_array);
}
