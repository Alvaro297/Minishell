/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:37:28 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/27 17:31:15 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static void	ft_free_memory(char **dest, int i)
{
	while (i >= 0)
	{
		i--;
		free(dest[i]);
	}
	free(dest);
}

static char	**ft_split2(char **dest, char const *s, char c, int lenght)
{
	char	*start;
	int		i;

	i = 0;
	while (*s)
	{
		lenght = 0;
		while (*s == c)
			s++;
		if (!*s)
			break ;
		start = (char *)s;
		while (*s && *s++ != c)
			lenght++;
		dest[i] = ft_substr(start, 0, lenght);
		if (!dest[i])
		{
			ft_free_memory(dest, i);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	return (ft_split2(dest, s, c, 0));
}
