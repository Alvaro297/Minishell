/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:26 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:26 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_append(char **command_splited)
{
	int	is_append;
	size_t	i;

	is_append = 0;
	i = 0;
	while (command_splited[i])
	{
		if (ft_strncmp(command_splited[i], ">>", 2) == 0)
			is_append = 2;
		else if (ft_strncmp(command_splited[i], ">", 1) == 0)
			is_append = 1;
		i++;
	}
	return (is_append);
}

char *find_infile(char **command_splited)
{
	char *infile;
	char *last_less_than;
	int i;

	i = 0;
	infile = NULL;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], "<", 1) == 0 &&
			 ft_strlen(command_splited[i]) == 1))
		{
			if (!check_name_arg(command_splited[i + 1]))
				return (NULL);
			else
			{
				if (infile)
					free(infile);
				infile = ft_strdup(command_splited[i + 1]);
			}
		}
		else if ((last_less_than = ft_strrchr(command_splited[i], '<')) != NULL)
		{
			const char *p = command_splited[i];
			while (*p)
			{
				if (*p == '<' && !is_within_quotes(command_splited[i], p))
				{
					if (infile)
						free(infile);
					infile = ft_strdup(p + 1);
				}
				p++;
			}
		}
		i++;
	}
	return (infile);
}

char *find_outfile(char **command_splited)
{
	char *outfile;
	char *last_greater_than;
	int i;

	i = 0;
	outfile = NULL;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], ">", 1) == 0 &&
			 ft_strlen(command_splited[i]) == 1))
		{
			if (!check_name_arg(command_splited[i + 1]))
				return (NULL);
			else
			{
				if (outfile)
					free(outfile);
				outfile = ft_strdup(command_splited[i + 1]);
			}
		}
		else if ((last_greater_than = ft_strrchr(command_splited[i], '>')) != NULL)
		{
			const char *p = command_splited[i];
			while (*p)
			{
				if (*p == '>' && !is_within_quotes(command_splited[i], p))
				{
					if (outfile)
						free(outfile);
					outfile = ft_strdup(p + 1);
				}
				p++;
			}
		}
		i++;
	}
	return (outfile);
}
