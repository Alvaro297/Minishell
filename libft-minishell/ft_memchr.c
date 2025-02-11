/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:44:19 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/27 14:14:49 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;

	src = (unsigned char *) s;
	c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (src[i] == c)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}
