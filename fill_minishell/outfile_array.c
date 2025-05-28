/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 19:00:11 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 19:00:11 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				break ;
			count++;
		}
		c++;
	}
	return (count);
}

char	**get_outfiles(char **command_splited, int c1)
{
	char	**outfile_array;
	int		c;
	int		size;

	size = get_size(command_splited);
	c = 0;
	if (size == 0)
		return (NULL);
	outfile_array = malloc(sizeof(char *) * (size + 1));
	while (command_splited[c])
	{
		if ((!ft_strncmp(command_splited[c], ">", 1)
				&& ft_strlen(command_splited[c]) == 1)
			|| (!ft_strncmp(command_splited[c], ">>", 2)
				&& ft_strlen(command_splited[c]) == 2))
		{
			outfile_array[c1] = ft_strdup(command_splited[c + 1]);
			c++;
			c1++;
		}
		c++;
	}
	outfile_array[c1] = NULL;
	return (outfile_array);
}
