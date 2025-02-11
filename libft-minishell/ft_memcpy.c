/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:00:35 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/27 17:01:41 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	str = (unsigned char *) dest;
	str_src = (unsigned char *) src;
	while (i < n)
	{
		str[i] = str_src[i];
		i++;
	}
	return (dest);
}
