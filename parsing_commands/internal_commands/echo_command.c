#include "../../minishell.h"

static char *expand_variable(t_minishell *minishell, char *str)
{
	const char	*var_name;
	const char	*var_value;

	if (str[0] != '$')
		return (ft_strdup(str));
	var_name = str + 1;
	var_value = get_env_value(minishell->env_vars, var_name);
	if (var_value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

static int	ft_sd_quote_printf(char *str, bool *in_single_quote,
		bool *in_double_quote, size_t *i)
{
	if (str[*i] == '\'' && !(*in_double_quote) && (i == 0 || str[*i - 1] != '\\'))
	{
		*in_single_quote = !(*in_single_quote);
		(*i)++;
		return (1);
	}
	if (str[*i] == '"' && !(*in_single_quote) && (i == 0 || str[*i - 1] != '\\'))
	{
		*in_double_quote = !(*in_double_quote);
		(*i)++;
		return (1);
	}
	return (0);
}

static int ft_quote_printf_ev(t_minishell minishell, char *str, t_indices *indices, char *result)
{
	char *expanded;

	expanded = expand_variable(minishell, &str[indices->i]);
	if (expanded != NULL)
	{
		ft_strcpy(&result[indices->j], expanded);
		indices->j += ft_strlen(expanded);
		free(expanded);
		while (str[indices->i] && str[indices->i] != ' ' &&
				str[indices->i] != '\'' && str[indices->i] != '"')
			indices->i++;
		indices->i--;
		return (1);
	}
	return (0);
}

static void	ft_quote_printf(t_minishell *minishell, char *str)
{
	bool		in_single_quote;
	bool		in_double_quote;
	char		*result;
	t_indices	indices;
	
	result = malloc(ft_strlen(str) + 1);
	if (result == NULL)
		return ;
	in_single_quote = false;
	in_double_quote = false;
	indices.j = 0;
	indices.i = 0;
	while (str[indices.i] != '\0')
	{
		if (ft_sd_quote_printf(str, &in_single_quote,
				&in_double_quote, &indices.i))
			continue ;
		if ((!in_single_quote && str[indices->i] == '$') &&
				ft_quote_printf_ev(minishell, str, &indices, result))
				continue ;
		result[indices.j++] = str[indices.i++];
	}
	result[indices.j] = '\0';
	printf("%s ", result);
	free(result);
}

int	handle_echo(t_minishell *minishell)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (minishell->input != NULL &&
			ft_strncmp(minishell->parsed_input[i], "-n", 2) == 0 &&
			ft_strlen(minishell->parsed_input[i]) == 2)
	{
		i++;
		newline = 0;
	}
	while (minishell->parsed_input[i] != NULL)
	{
		ft_quote_printf(minishell, minishell->parsed_input[i]);
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}
