/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controled_errors_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 20:15:08 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 20:15:08 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	here_doc_delim_check_error(char *command)
{
	char		**split_input_inic;
	int			count_heredocs;

	split_input_inic = split_modified(command, ' ');
	split_input_inic = process_redirection(split_input_inic);
	count_heredocs = ft_count_heredocs(split_input_inic);
	if (count_heredocs == -1)
	{
		ft_putstr_fd("Syntax error near unexpected token\n", 2);
		free_double_array((void **)split_input_inic);
		return (false);
	}
	free_double_array((void **)split_input_inic);
	return (true);
}

static bool	find_infile_check_error(t_minishell *minishell,
		char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], "<", 1) == 0
				&& ft_strlen(command_splited[i]) == 1))
		{
			if (!command_splited[i + 1]
				|| is_redirected(command_splited[i + 1]))
			{
				if (!command_splited[i + 1])
					ft_putstr_fd("Syntax error near unexpected token\n", 2);
				else
					ft_putstr_fd("Syntax error near unexpected token\n", 2);
				return (false);
			}
			else if (is_env_var_null(minishell, command_splited[i + 1]))
				return (ft_putstr_fd("Ambiguous redirect\n", 2), false);
		}
		i++;
	}
	return (true);
}

static bool	find_outfile_check_error(t_minishell *minishell,
		char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], ">", 1) == 0
				&& ft_strlen(command_splited[i]) == 1)
			|| (ft_strncmp(command_splited[i], ">>", 2) == 0
				&& ft_strlen(command_splited[i]) == 2))
		{
			if (!command_splited[i + 1]
				|| is_redirected(command_splited[i + 1]))
			{
				ft_putstr_fd("Syntax error near unexpected token\n", 2);
				return (false);
			}
			else if (is_env_var_null(minishell, command_splited[i + 1]))
			{
				ft_putstr_fd("Syntax error near unexpected token\n", 2);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	set_exit_code_and_return(t_minishell *minishell, int code)
{
	char *exit_code;
	
	exit_code = ft_itoa(code);
	set_env(&minishell->env_vars, "?", exit_code);
	free(exit_code);
	return (false);
}

bool	controled_errors(t_minishell *minishell,
		char **command_splited, t_parse_data *data)
{
	bool	success;

	success = here_doc_delim_check_error(data->command);
	if (!success)
		return (set_exit_code_and_return(minishell, 2));
	success = find_outfile_check_error(minishell, command_splited);
	if (!success)
		return (set_exit_code_and_return(minishell, 2));
	success = find_infile_check_error(minishell, command_splited);
	if (!success)
		return (set_exit_code_and_return(minishell, 2));
	success = check_pipes(data->array_commands, data->position);
	if (!success)
		return (set_exit_code_and_return(minishell, 2));
	return (true);
}
