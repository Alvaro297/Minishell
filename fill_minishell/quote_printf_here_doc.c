# include "../minishell.h"


static char *expand_variable_here_doc(t_minishell *minishell, char *str, size_t *len)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '?')
	{
		*len = 2;
		return (ft_itoa(minishell->last_exit_status));
	}
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_strndup(str + 1, i - 1);
	var_value = get_env_value(minishell->env_vars, var_name);
	*len = i;
	if (var_value == NULL)
		return (NULL);
	return (ft_strdup(var_value));
}

static int ft_quote_printf_ev_here_doc(t_minishell *minishell, char *str, t_indices *indices, char **result)
{
	char	*expanded;
	size_t	len;

	expanded = expand_variable_here_doc(minishell, &str[indices->i], &len);
	if (expanded != NULL)
	{
		append_expanded_variable_no_quotes(result, &indices->j, expanded);
		free(expanded);
	}
	else
		append_expanded_variable_no_quotes(result, &indices->j, "");
	indices->i += len;
	printf("Expanded: %s\n", *result); // Debugging line
	return (expanded != NULL);
}

static void	ft_quote_printf_help(char **result, t_indices *indices, char *str)
{
	char	*new_result;

	new_result = malloc(indices->j + 2);
	if (new_result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new_result, *result, indices->j + 1);
	new_result[indices->j] = str[indices->i];
	new_result[indices->j + 1] = '\0';
	free(*result);
	*result = new_result;
	indices->j++;
	indices->i++;
}

static void	ft_quote_printf_loop_here_doc(t_minishell *minishell, char *str, t_indices *indices, char **result)
{
	while (str[indices->i] != '\0')
	{
		if (str[indices->i] == '$' && str[indices->i + 1] != '\0'
					&& str[indices->i + 1] != ' ' && str[indices->i + 1] != '$')
		{
			if (ft_quote_printf_ev_here_doc(minishell, str, indices, result))
				continue ;
		}
		ft_quote_printf_help(result, indices, str);
	}
}

char	*ft_quote_printf_here_doc(t_minishell *minishell, char *str)
{
	char		*result;
	t_indices	indices;

	result = ft_strdup("");
	indices.i = 0;
	indices.j = 0;
	ft_quote_printf_loop_here_doc(minishell, str, &indices, &result);
	result[indices.j] = '\0';
	printf("Result: %s\n", result); // Debugging line
	return (result);
}
