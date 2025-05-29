/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 19:06:03 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 19:06:03 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_expanded_variable_no_quotes(char **result,
		size_t *j, char *expanded)
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

void	append_expanded_variable(char **result, size_t *j, char *expanded)
{
	size_t		len;
	size_t		current_len;
	char		*adapted_result;

	len = ft_strlen(expanded);
	current_len = *j;
	adapted_result = malloc(current_len + len + 3);
	if (adapted_result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(adapted_result, *result, current_len + 1);
	adapted_result[current_len] = '"';
	ft_strlcpy(&adapted_result[current_len + 1], expanded, len + 1);
	adapted_result[current_len + len + 1] = '"';
	adapted_result[current_len + len + 2] = '\0';
	free(*result);
	*result = adapted_result;
	*j += len + 2;
}

void	ft_quote_printf_cleanup(t_minishell *minishell,
		t_quotes quotes, char **result, bool is_input)
{
	if (minishell->input != NULL && is_input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (*result && **result == '\0'
		&& !quotes.in_single_quote && !quotes.in_double_quote)
	{
		free(*result);
		*result = NULL;
	}
	if (quotes.in_single_quote || quotes.in_double_quote)
		handle_unclosed_quotes(minishell, quotes, result);
}
