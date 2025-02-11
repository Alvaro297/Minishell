/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:33:30 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/16 18:33:30 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	end = (char *)s;
	while (*end != '\0')
		end++;
	if (c == '\0')
		return ((char *) end);
	while (end >= s)
	{
		if (*end == (char) c)
		{
			return ((char *) end);
		}
		end--;
	}
	return (NULL);
}
