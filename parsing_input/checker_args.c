/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:32 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:32 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_name_arg(char	*name)
{
	t_quotes	quotes;
	size_t		i;
	int			j;

	i = 0;
	quotes.in_double_quote = false;
	quotes.in_single_quote = false;
	while (name[i])
	{
		ft_sd_quote_printf(name, &quotes, &i);
		if (!quotes.in_single_quote && !quotes.in_double_quote)
		{
			j = 0;
			while (INVALID_CHARACTERS[j])
			{
				if (INVALID_CHARACTERS[j] == name[i])
					return (false);
				j++;
			}
		}
		i++;
	}
	return (true);
}
