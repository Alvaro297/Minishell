/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 18:07:42 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-07 18:07:42 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int count_commands(const char *input)
{
	int count;
	int i;
	t_quotes quotes;

	i = 0;
	count = 0;
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	while (input[i])
	{
		if (input[i] == '\'' && !quotes.in_double_quote)
			quotes.in_single_quote = !quotes.in_single_quote;
		else if (input[i] == '"' && !quotes.in_single_quote)
			quotes.in_double_quote = !quotes.in_double_quote;
		if (input[i] == '|' && !quotes.in_single_quote && !quotes.in_double_quote)
			count += 2;
		i++;
	}
	return (count + 1);
}

static char **split_commands(const char *input, int i, t_quotes *quotes)
{
	char	**commands;
	int		cmd_index;
	int		start;
	
	commands = malloc((count_commands(input) + 1) * sizeof(char *));
	cmd_index = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !quotes->in_double_quote)
			quotes->in_single_quote = !quotes->in_single_quote;
		else if (input[i] == '"' && !quotes->in_single_quote)
			quotes->in_double_quote = !quotes->in_double_quote;
		if (input[i] == '|' && !quotes->in_single_quote && !quotes->in_double_quote)
		{
			commands[cmd_index++] = ft_strndup(input + start, i - start);
			commands[cmd_index++] = ft_strndup(input + i, 1);
			start = i + 1;
		}
		i++;
	}
	if (start < (int)ft_strlen(input))
		commands[cmd_index++] = ft_strdup(input + start);
	commands[cmd_index] = NULL;
	return (commands);
}

static bool	parse_input_help(t_minishell *minishell, t_cmd **new_cmd, t_parse_data *data)
{
	t_cmd	*tmp;
	char	**command_splited;
	
	tmp = malloc(sizeof(t_cmd));
	init_cmd(tmp);
	*new_cmd = tmp;
	command_splited = split_modified(data->command, ' ');
	command_splited = process_redirection(command_splited);
	if (!controled_errors(minishell, command_splited, data))
	{
		free_double_array((void **)command_splited);
		free(tmp);
		return (false);
	}
	tmp->cmd = find_command(minishell, command_splited);
	tmp->args = find_args(minishell, command_splited);
	tmp->is_pipe = have_pipe(data->array_commands, data->position);
	tmp->outfile = find_outfile(command_splited);
	tmp->infile = find_infile(command_splited);
	tmp->is_heredoc = is_heredoc(command_splited);
	tmp->here_doc_delim = here_doc_delim(data->command);
	tmp->outfile_array = get_outfiles(command_splited);
	tmp->outfile_modes = is_append(command_splited);
	tmp->next = NULL;
	delete_quotes(minishell, tmp);
	free_double_array((void **)command_splited);
	return (true);
}

static void	parse_input_loop(t_minishell *minishell, t_cmd **head, char **parsed_input)
{
	t_cmd	*new_cmd;
	t_parse_data	data;
	bool	is_all_ok;

	data.position = 0;
	data.array_commands = parsed_input;
	is_all_ok = true;
	while (parsed_input[data.position])
	{
		data.command = parsed_input[data.position];
		is_all_ok = parse_input_help(minishell, &new_cmd, &data);
		if (!is_all_ok)
		{
			free_cmd_list(*head);
			head = NULL;
			break ;
		}
		append_cmds(head, new_cmd);
		if (new_cmd->is_pipe)
			data.position += 2;
		else
			break ;
	}
}

t_cmd	*parsing_input(t_minishell *minishell, char *input)
{
	t_cmd	*head;
	char	**parsed_input;
	t_quotes quotes;
	t_parse_data data;

	head = NULL;
	if (minishell->cmds)
		delete_cmds(minishell->cmds);
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	data.input = ft_strdup(input);
	parsed_input = split_commands(data.input, 0, &quotes);
	parse_input_loop(minishell, &head, parsed_input);
	free(data.input);
	free_double_array((void **)parsed_input);
	return (head);
}
