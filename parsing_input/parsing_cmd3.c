# include "../minishell.h"

bool	have_pipe(char **command, int position)
{
	int	position_pipe;

	position_pipe = position + 1;
	if (command[position_pipe] &&
		ft_strncmp(command[position_pipe], "|", 1) == 0 &&
		ft_strlen(command[position_pipe]) == 1)
		return (true);
	return (false);
}

bool	is_append(char **command_splited)
{
	bool	is_append;
	size_t	i;

	is_append = false;
	i = 0;
	while (command_splited[i])
	{
		if (ft_strncmp(command_splited[i], ">>", 2) == 0 &&
			ft_strlen(command_splited[i]) == 2)
			is_append = true;
		else if ((ft_strncmp(command_splited[i], ">", 1) == 0 &&
					ft_strlen(command_splited[i]) == 1) ||
				(ft_strncmp(command_splited[i], "1>", 2) == 0 &&
					ft_strlen(command_splited[i]) == 2))
			is_append = false;
		i++;
	}
	return (is_append);
}

char	*find_infile(char **command_splited)
{
	char	*infile;
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], "<", 1) == 0 &&
					ft_strlen(command_splited[i]) == 1) ||
				(ft_strncmp(command_splited[i], "0<", 2) == 0 &&
					ft_strlen(command_splited[i]) == 2))
		{
			i++;
			if (!check_name_arg(command_splited[i]))
				return (NULL);
			else
				infile = ft_strdup(command_splited[i]);
		}
		i++;
	}
	return (infile);
}

char	*find_outfile(char **command_splited)
{
	char	*outfile;
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], ">", 1) == 0 &&
					ft_strlen(command_splited[i]) == 1) ||
				(ft_strncmp(command_splited[i], ">>", 2) == 0 &&
					ft_strlen(command_splited[i]) == 2) ||
				(ft_strncmp(command_splited[i], "1>", 2) == 0 &&
					ft_strlen(command_splited[i]) == 2))
		{
			i++;
			if (!check_name_arg(command_splited[i]))
				return (NULL);
			else
				outfile = ft_strdup(command_splited[i]);
		}
		i++;
	}
	return (outfile);
}
