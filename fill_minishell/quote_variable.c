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

char *ft_sd_quote_printf_mod2(char *str, t_quotes *quotes)
{
	if (*str == '\'' && !(quotes->in_double_quote))
	{
		quotes->in_single_quote = !(quotes->in_single_quote);
		return (++str);
	}
	if (*str == '"' && !(quotes->in_single_quote))
	{
		quotes->in_double_quote = !(quotes->in_double_quote);
		return (++str);
	}
	return (str);
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


bool is_within_quotes(const char *str, const char *pos)
{
	bool in_single_quote;
	bool in_double_quote;
	const char *p;

	p = str;
	in_double_quote = false;
	in_single_quote = false;
	while (p < pos)
	{
		if (*p == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*p == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		p++;
	}
	return (in_single_quote || in_double_quote);
}
