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

#include "../minishell.h"

static char	*expand_variable(t_minishell *minishell, char *str, size_t *len)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (str[0] != '$')
		return (ft_strdup(str));
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	var_name = ft_strndup(str + 1, i - 1);
	var_value = get_env_value(minishell->env_vars, var_name, true);
	*len = i;
	if (var_value == NULL)
		return (NULL);
	return (ft_strdup(var_value));
}

static int	ft_quote_printf_ev(char *str, t_quote_ctx *ctx)
{
	char	*expanded;
	size_t	len;

	expanded = expand_variable(ctx->minishell, &str[ctx->indices->i], &len);
	if (expanded != NULL)
	{
		if (!ctx->quotes->in_single_quote && !ctx->quotes->in_double_quote)
			append_expanded_variable(ctx->result, &ctx->indices->j, expanded);
		else
			append_expanded_variable_no_quotes(ctx->result,
				&ctx->indices->j, expanded);
		free(expanded);
	}
	else
	{
		if (ctx->quotes->in_single_quote || ctx->quotes->in_double_quote)
			append_expanded_variable_no_quotes(ctx->result,
				&ctx->indices->j, "");
	}
	ctx->indices->i += len;
	return (expanded != NULL
		|| (ctx->quotes->in_single_quote || ctx->quotes->in_double_quote));
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

static void	ft_quote_printf_loop(char *str, t_quote_ctx *ctx)
{
	tabs_to_spaces(str);
	while (str[ctx->indices->i] == ' ')
		ctx->indices->i++;
	while (str[ctx->indices->i] != '\0')
	{
		if (ft_sd_quote_printf_mod(str, ctx->quotes, ctx->indices->i))
		{
			ft_quote_printf_help(ctx->result, ctx->indices, str);
			continue ;
		}
		if (!ctx->quotes->in_single_quote
			&& (str[ctx->indices->i] == '$'
				&& str[ctx->indices->i + 1] != '\0'
				&& str[ctx->indices->i + 1] != ' '
				&& str[ctx->indices->i + 1] != '$'))
		{
			if (ft_quote_printf_ev(str, ctx))
				continue ;
			if (!ctx->quotes->in_single_quote && !ctx->quotes->in_double_quote)
				continue ;
		}
		ft_quote_printf_help(ctx->result, ctx->indices, str);
	}
}

char	*ft_quote_printf(t_minishell *minishell, char *str, bool is_input)
{
	t_quotes	quotes;
	char		*result;
	t_indices	indices;
	t_quote_ctx	ctx;

	if (ft_strrchr(str, '\n') != NULL)
	{
		ft_putstr_fd ("warning: newline at end of input\n", STDERR_FILENO);
		result = ft_itoa(1);
		set_env(&minishell->env_vars, "?", result);
		return (free(result), NULL);
	}
	result = ft_strdup("");
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	indices.i = 0;
	indices.j = 0;
	ctx.minishell = minishell;
	ctx.quotes = &quotes;
	ctx.indices = &indices;
	ctx.result = &result;
	ft_quote_printf_loop(str, &ctx);
	result[indices.j] = '\0';
	ft_quote_printf_cleanup(minishell, quotes, &result, is_input);
	return (result);
}
