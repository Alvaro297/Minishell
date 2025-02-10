# include "../minishell.h"

bool	check_name_arg(char	*name)
{
	bool	in_single_quote;
	bool	in_double_quote;
	size_t	i;
	int		j;

	i = 0;
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
