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

int	ft_sd_quote_printf_mod(char *str, bool *in_single_quote,
		bool *in_double_quote, size_t *i)
{
	if (str[*i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (1);
	}
	if (str[*i] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (1);
	}
	return (0);
}

int	ft_sd_quote_printf(char *str, bool *in_single_quote,
	bool *in_double_quote, size_t *i)
{
	if (str[*i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*i)++;
		return (1);
	}
	if (str[*i] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_sd_quote_printf_mod2(char **str, bool *in_single_quote,
	bool *in_double_quote)
{
	if (**str == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*str)++;
		return (1);
	}
	if (**str == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*str)++;
		return (1);
	}
	return (0);
}

char *ft_sd_quote_printf_mod3(char *str, bool *in_single_quote, bool *in_double_quote)
{
	if (*str == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (++str);
	}
	if (*str == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (++str);
	}
	return (str);
}