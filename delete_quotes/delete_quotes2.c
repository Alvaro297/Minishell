/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 21:21:55 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 21:21:55 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*delete_quotes_single(t_minishell *minishell,
		char *str, bool is_not_here_doc)
{
	char	*result;

	result = delete_quotes_array(minishell, str, is_not_here_doc, false);
	return (result);
}

char	**delete_quotes_double_array(t_minishell *minishell,
		char **double_array, bool is_not_here_doc)
{
	int		i;
	int		count;
	char	**tmp;

	if (double_array == NULL)
		return (NULL);
	count = 0;
	while (double_array[count])
		count++;
	tmp = malloc(sizeof(char *) * (count + 1));
	if (tmp == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (double_array[i])
	{
		tmp[i] = delete_quotes_single(minishell,
				double_array[i], is_not_here_doc);
		i++;
	}
	tmp[i] = NULL;
	free(double_array);
	return (tmp);
}
