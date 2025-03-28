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
/*
static void print_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
	{
		printf("Command is NULL\n");
		return;
	}

	printf("Command: %s\n", cmd->cmd);

	printf("Arguments: ");
	if (cmd->args)
	{
		for (i = 0; cmd->args[i]; i++)
		{
			printf("%s ", cmd->args[i]);
		}
	}
	printf("\n");

	printf("Is Pipe: %d\n", cmd->is_pipe);
	printf("Infile: %s\n", cmd->infile);
	printf("Outfile: %s\n", cmd->outfile);

	printf("Outfile Array: ");
	if (cmd->outfile_array)
	{
		for (i = 0; cmd->outfile_array[i]; i++)
		{
			printf("%s ", cmd->outfile_array[i]);
		}
	}
	printf("\n");
	printf("Outfile Modes: %d", cmd->outfile_modes);
	printf("\n");
}*/

void init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->is_pipe = false;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->outfile_array = NULL;
	cmd->outfile_modes = 0;
	cmd->is_heredoc = false;
	cmd->here_doc_delim = NULL;
	cmd->next = NULL;
}

static void	parse_input_help(t_minishell *minishell, t_cmd **new_cmd, t_parse_data *data)
{
	t_cmd	*tmp;
	char	**command_splited;
	int		i;
	
	tmp = malloc(sizeof(t_cmd));
	init_cmd(tmp);
	*new_cmd = tmp;
	command_splited = split_modified(data->command, ' ');
	command_splited = process_redirection(command_splited);
	tmp->cmd = find_command(minishell, command_splited);
	tmp->args = find_args(minishell, command_splited);
	tmp->is_pipe = have_pipe(data->array_commands, data->position);
	tmp->infile = find_infile(minishell, command_splited);
	tmp->outfile = find_outfile(minishell, command_splited);
	tmp->outfile_array = get_outfiles(minishell, command_splited);
	tmp->outfile_modes = is_append(command_splited);
	tmp->is_heredoc = is_heredoc(command_splited);
	tmp->here_doc_delim = here_doc_delim(data->input);
	if (tmp->here_doc_delim)
	{
	    printf("Here-doc Delimiters:\n");
	    for (i = 0; tmp->here_doc_delim[i] != NULL; i++)
	    {
	        printf("  Delimiter %d: %s\n", i, tmp->here_doc_delim[i]);
	    }
	}
	else
	{
	    printf("Here-doc Delimiters: NULL\n");
	}
	tmp->next = NULL;
	delete_quotes(minishell, tmp);
	i = 0;
	while (command_splited[i] != NULL)
		free(command_splited[i++]);
	free(command_splited);
}

t_cmd	*parsing_input(t_minishell *minishell, char *input)
{
	t_cmd		*head = NULL;
	t_cmd		*new_cmd = NULL;
	char		**parsed_input;
	t_quotes	quotes;
	t_parse_data data;

	if (minishell->cmds)
		delete_cmds(minishell->cmds);
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	parsed_input = split_commands(input, 0, &quotes);
	data.position = 0;
	data.array_commands = parsed_input;
	data.input = input;
	while (parsed_input[data.position])
	{
		data.command = parsed_input[data.position];
		parse_input_help(minishell, &new_cmd, &data);
		append_cmds(&head, new_cmd);
		if (head->is_pipe)
			data.position += 2;
		else
			break ;
	}
	return (head);
}
