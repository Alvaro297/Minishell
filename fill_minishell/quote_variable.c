#include "../minishell.h"

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
