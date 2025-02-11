/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:54:16 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/27 12:47:28 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str_s1;
	const unsigned char	*str_s2;
	size_t				i;

	i = 0;
	str_s1 = (const unsigned char *) s1;
	str_s2 = (const unsigned char *) s2;
	while (i < n)
	{
		if (str_s1[i] == str_s2[i])
			i++;
		else
			return (str_s1[i] - str_s2[i]);
	}
	return (0);
}
