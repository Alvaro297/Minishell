# include "../minishell.h"

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

static bool	find_infile_check_error(t_minishell *minishell, char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], "<", 1) == 0 &&
				ft_strlen(command_splited[i]) == 1))
		{
			if (!command_splited[i + 1] || is_redirected(command_splited[i + 1]))
				{
					if (!command_splited[i + 1])
						printf("Syntax error near unexpected token 'newline'\n");
					else
						printf("Syntax error near unexpected token '%s'\n", command_splited[i + 1]);
					return (false);
				}
			else if (is_env_var_null(minishell, command_splited[i + 1]))
				return (printf("%s: ambiguous redirect\n", command_splited[i + 1]), false);
		}
		i++;
	}
	return (true);
}

static bool	find_outfile_check_error(t_minishell *minishell, char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], ">", 1) == 0 &&
			 ft_strlen(command_splited[i]) == 1) || 
			 (ft_strncmp(command_splited[i], ">>", 2) == 0 &&
			 ft_strlen(command_splited[i]) == 2))
		{
			if (!command_splited[i + 1] || is_redirected(command_splited[i + 1]))
				{
					if (!command_splited[i + 1])
						printf("Syntax error near unexpected token 'newline'\n");
					else
						printf("Syntax error near unexpected token '%s'\n", command_splited[i + 1]);
					return (false);
				}
			else if (is_env_var_null(minishell, command_splited[i + 1]))
				return (printf("%s: ambiguous redirect\n", command_splited[i + 1]), false);
		}
		i++;
	}
	return (true);
}

static int	is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return 0;
		str++;
	}
	return 1;
}

static bool	check_pipes(char **array_commands, int position)
{
	int		position_pipe;

	position_pipe = position + 1;
	if (array_commands[position_pipe])
	{
		if (ft_strncmp(array_commands[position_pipe], "|", 1) == 0 &&
					 (!array_commands[position_pipe + 1] ||
						array_commands[position_pipe + 1][0] == '\0' ||
						is_all_spaces(array_commands[position_pipe + 1])))
			return (printf("Syntax error near unexpected token3 'newline'\n"), false);
		else if (position_pipe == 1 && array_commands[position][0] == '\0')
		{
			if (ft_strncmp(array_commands[position_pipe], "|", 1) == 0)
				return (printf("Syntax error near unexpected token '|'\n"), false);
		}
		else if (array_commands[position_pipe][0] == '|' &&
					array_commands[position_pipe + 1][0] == '|')
			return (printf("Syntax error near unexpected token2 '|'\n"), false);
	}
	return (true);
}

bool	controled_errors(t_minishell *minishell, char **command_splited, t_parse_data *data)
{
	bool	success;

	success = true;
	success = here_doc_delim_check_error(data->command);
	if (!success)
		return (set_env(&minishell->env_vars, "?", ft_itoa(2)), false);
	success = find_outfile_check_error(minishell, command_splited);
	if (!success)
		return (set_env(&minishell->env_vars, "?", ft_itoa(2)), false);
	success = find_infile_check_error(minishell, command_splited);
	if (!success)
		return (set_env(&minishell->env_vars, "?", ft_itoa(2)), false);
	success = check_pipes(data->array_commands, data->position);
	if (!success)
		return (set_env(&minishell->env_vars, "?", ft_itoa(2)), false);
	return (true);
}