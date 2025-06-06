/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controled_errors_parsing2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 20:14:26 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 20:14:26 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_unclosed_quotes(t_minishell *minishell,
		t_quotes quotes, char **result)
{
	set_special_var_input_null(minishell, *result);
	free(*result);
	*result = NULL;
	if (quotes.in_single_quote)
		write(2, "minishell: unclosed single quote\n", 34);
	else
		write(2, "minishell: unclosed double quote\n", 34);
	set_env(&minishell->env_vars, "?", "2");
}

static int	is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

static bool	check_pipe_newline(char **array_commands, int position_pipe)
{
	if (ft_strncmp(array_commands[position_pipe], "|", 1) == 0
		&& (!array_commands[position_pipe + 1]
			|| array_commands[position_pipe + 1][0] == '\0'
		|| is_all_spaces(array_commands[position_pipe + 1])))
	{
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", 2);
		return (false);
	}
	return (true);
}

bool	check_pipes(char **array_commands, int position)
{
	int		position_pipe;

	position_pipe = position + 1;
	if (array_commands[position_pipe])
	{
		if (!check_pipe_newline(array_commands, position_pipe))
			return (false);
		else if (position_pipe == 1 && array_commands[position][0] == '\0')
		{
			if (ft_strncmp(array_commands[position_pipe], "|", 1) == 0)
			{
				ft_putstr_fd("Syntax error near unexpected token '|'\n", 2);
				return (false);
			}
		}
		else if (array_commands[position_pipe][0] == '|' &&
					array_commands[position_pipe + 1][0] == '|')
		{
			ft_putstr_fd("Syntax error near unexpected token2 '|'\n", 2);
			return (false);
		}
	}
	return (true);
}
