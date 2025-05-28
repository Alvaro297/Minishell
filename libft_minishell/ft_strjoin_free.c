/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:48:06 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 18:48:06 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*space_memory;
	size_t	len_s1;
	size_t	len_s2;

	space_memory = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!space_memory)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ft_strlcpy(space_memory, (char *)s1, len_s1 + 1);
	ft_strlcat(space_memory, s2, len_s1 + len_s2 + 1);
	free (s1);
	return (space_memory);
}
