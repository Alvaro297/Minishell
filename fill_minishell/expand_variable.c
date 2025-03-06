/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:32:39 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:32:39 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

static void append_expanded_variable(char **result, size_t *j, const char *expanded)
{
	size_t		len;
	size_t		current_len;
	char		*adapted_result;

	len = ft_strlen(expanded);
	current_len = *j;
	adapted_result = malloc(current_len + len + 1);
	if (adapted_result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(adapted_result, *result, current_len + 1);
	adapted_result[current_len] = '\0';
	ft_strlcat(adapted_result, expanded, current_len + len + 1);
	free(*result);
	*result = adapted_result;
	*j += len;
}

static char *expand_variable(t_minishell *minishell, char *str, size_t *len)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '?')
	{
		*len = 2;
		if (str[1] == '?')
			return (ft_itoa(minishell->last_exit_status));
	}
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_strndup(str + 1, i - 1);
	var_value = get_env_value(minishell->env_vars, var_name);
	free(var_name);
	*len = i;
	if (var_value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

static int ft_quote_printf_ev(t_minishell *minishell, char *str, t_indices *indices, char **result)
{
	char *expanded;
	size_t len;

	expanded = expand_variable(minishell, &str[indices->i], &len);
	if (expanded != NULL)
	{
		append_expanded_variable(result, &indices->j, expanded);
		indices->i += len;
		free(expanded);
		return (1);
	}
	return (0);
}

static void	ft_quote_printf_help(char **result, t_indices *indices, char *str)
{
	char *new_result;
	
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

char	*ft_quote_printf(t_minishell *minishell, char *str)
{
	bool		in_single_quote;
	bool		in_double_quote;
	char		*result;
	char		*new_result;
	t_indices	indices;
	
	result = ft_strdup("");
	in_single_quote = false;
	in_double_quote = false;
	indices.i = 0;
	indices.j = 0;
	while (str[indices.i] != '\0')
	{
		if (ft_sd_quote_printf_mod(str, &in_single_quote,
				&in_double_quote, &indices.i))
				{
					ft_quote_printf_help(&result, &indices, str);
					continue ;
				}
		if ((!in_single_quote && str[indices.i] == '$') &&
				ft_quote_printf_ev(minishell, str, &indices, &result))
				continue ;
		ft_quote_printf_help(&result, &indices, str);
	}
	return (result);
}
