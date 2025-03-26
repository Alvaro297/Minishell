# include "../minishell.h"

bool	is_heredoc(char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if (ft_strcmp(command_splited[i], "<<") == 0)
			return (true);
		i++;
	}
	return (false);
}

static int	ft_count_heredocs(char **command_splited)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (command_splited[i])
	{
		if (ft_strncmp(command_splited[i], "<<", 2) == 0)
		{
			if (command_splited[i][2])
			{
				/* code */
			}
			else if (command_splited[i + 1] && !is_redirected(command_splited[i + 1]))
			{
				i++;
				count++;
			}
			else
				return (-1);
		}
		i++;
	}
	return (count);
}

static char	**here_doc_delim_help(char **command_splited, char **heredocs_delim)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (command_splited[i])
	{
		if (ft_strncmp(command_splited[i], "<<", 2) == 0)
		{
			if (command_splited[i + 1] && !is_redirected(command_splited[i + 1]))
			{
				i++;
				heredocs_delim[count] = ft_strdup(command_splited[i]);
				if (!heredocs_delim[count])
					return (free_double_array((void **) heredocs_delim), NULL);
				count++;
			}
			else
				return (NULL);
		}
		i++;
	}
	heredocs_delim[count] = NULL;
	return (heredocs_delim);
}

char	**here_doc_delim(char **command_splited)
{
	char		**heredocs_delim;
	int			count_heredocs;

	count_heredocs = ft_count_heredocs(command_splited);
	if (count_heredocs == -1)
	{
		ft_putstr_fd("Syntax error near unexpected token\n", 2);
		return (NULL);
	}
	heredocs_delim = malloc(sizeof(char *) * (count_heredocs + 1));
	return(here_doc_delim_help(command_splited, heredocs_delim));
}
