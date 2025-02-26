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

# include "../minishell.h"

bool	check_name_arg(char	*name)
{
	bool	in_single_quote;
	bool	in_double_quote;
	size_t	i;
	int		j;

	i = 0;
	in_double_quote = false;
	in_single_quote = false;
	while (name[i])
	{
		ft_sd_quote_printf(name, &in_single_quote, &in_double_quote, &i);
		if (!in_single_quote && !in_double_quote)
		{
			j = 0;
			while (INVALID_CHARACTERSV[j])
			{
				if (INVALID_CHARACTERSV[j] == name[i])
					return (false);
				j++;
			}
		}
		i++;
	}
	return (true);
}
