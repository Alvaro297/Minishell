/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:54:34 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 18:54:34 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double_array(void **double_array)
{
	int	i;

	i = 0;
	if (!double_array)
		return ;
	while (double_array[i])
	{
		free(double_array[i]);
		i++;
	}
	free(double_array);
}
