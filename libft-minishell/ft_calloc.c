/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:38:38 by alvamart          #+#    #+#             */
/*   Updated: 2024/10/02 11:45:29 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num != 0 && size > (size_t)(-1) / num)
		return (NULL);
	ptr = malloc(size * num);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (num * size));
	return (ptr);
}
