/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:32:25 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:32:25 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sd_quote_printf_mod(char *str, t_quotes *quotes, size_t i)
{
	if (str[i] == '\'' && !(quotes->in_double_quote))
	{
		quotes->in_single_quote = !(quotes->in_single_quote);
		return (1);
	}
	if (str[i] == '"' && !(quotes->in_single_quote))
	{
		quotes->in_double_quote = !(quotes->in_double_quote);
		return (1);
	}
	return (0);
}

int	ft_sd_quote_printf(char *str, t_quotes *quotes, size_t *i)
{
	if (str[*i] == '\'' && !(quotes->in_double_quote))
	{
		quotes->in_single_quote = !(quotes->in_single_quote);
		(*i)++;
		return (1);
	}
	if (str[*i] == '"' && !(quotes->in_single_quote))
	{
		quotes->in_double_quote = !(quotes->in_double_quote);
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_sd_quote_printf_mod3(char *str, t_quotes *quotes)
{
	if (*str == '\'' && !(quotes->in_double_quote))
	{
		quotes->in_single_quote = !(quotes->in_single_quote);
		++str;
	}
	if (*str == '"' && !(quotes->in_single_quote))
	{
		quotes->in_double_quote = !(quotes->in_double_quote);
		++str;
	}
}

