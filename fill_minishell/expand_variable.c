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
		return (NULL); // Devuelve NULL si la variable no existe
	return (ft_strdup(var_value));
}

static int ft_quote_printf_ev(t_minishell *minishell, char *str, t_indices *indices, char **result, t_quotes *quotes)
{
	char	*expanded;
	size_t	len;

	expanded = expand_variable(minishell, &str[indices->i], &len);
	if (expanded != NULL)
	{
		// Si la expansión no es NULL, agregarla al resultado
		if (!quotes->in_single_quote && !quotes->in_double_quote)
			append_expanded_variable(result, &indices->j, expanded);
		else
			append_expanded_variable_no_quotes(result, &indices->j, expanded);
		free(expanded);
	}
	else
	{
		// Si la expansión es NULL y está entre comillas, agregar una cadena vacía
		if (quotes->in_single_quote || quotes->in_double_quote)
			append_expanded_variable_no_quotes(result, &indices->j, "");
	}
	indices->i += len;
	return (expanded != NULL || (quotes->in_single_quote || quotes->in_double_quote));
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

static void	ft_quote_printf_loop(t_minishell *minishell, char *str, t_quotes *quotes, t_indices *indices, char **result)
{
	while (str[indices->i] != '\0')
	{
		if (ft_sd_quote_printf_mod(str, quotes, indices->i))
		{
			ft_quote_printf_help(result, indices, str);
			continue ;
		}
		if ((!quotes->in_single_quote && str[indices->i] == '$'))
		{
			if (ft_quote_printf_ev(minishell, str, indices, result, quotes))
				continue ;
			if (!quotes->in_single_quote && !quotes->in_double_quote)
				continue ;
		}
		ft_quote_printf_help(result, indices, str);
	}
}

char	*ft_quote_printf(t_minishell *minishell, char *str)
{
	t_quotes	quotes;
	char		*result;
	t_indices	indices;

	if (minishell->input != NULL)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	result = ft_strdup("");
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	indices.i = 0;
	indices.j = 0;
	ft_quote_printf_loop(minishell, str, &quotes, &indices, &result);
	result[indices.j] = '\0';
	if (quotes.in_single_quote || quotes.in_double_quote)
	{
		free(result);
		result = NULL;
		if (quotes.in_single_quote)
			write(2, "minishell: unclosed single quote\n", 34);
		else
			write(2, "minishell: unclosed double quote\n", 34);
	}
	return (result);
}
