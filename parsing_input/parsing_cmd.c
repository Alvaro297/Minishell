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

static bool is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int count_commands(const char *input)
{
	int count;
	int i;
	bool in_single_quote;
	bool in_double_quote;

	i = 0;
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (input[i] == '|' &&
				!in_single_quote && !in_double_quote)
			count += 2;
		i++;
	}
	return (count + 1);
}

static char **split_commands(const char *input, int i,
		bool in_single_quote, bool in_double_quote)
{
	char	**commands;
	int		cmd_index;
	int		start;
	
	commands = malloc((count_commands(input) + 1) * sizeof(char *));
	cmd_index = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (is_special_char(input[i]) && !in_single_quote && !in_double_quote)
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

static void	parse_input_help(t_cmd **new_cmd, char *command, int position, char **array_commands)
{
	t_cmd	*tmp;
	char	**command_splited;
	
	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return ;
	tmp = *new_cmd;
	command_splited = split_modified(command, ' ');
	tmp->cmd = find_command(command_splited);
	tmp->args = find_args(command_splited);
	tmp->is_pipe = have_pipe(array_commands, position);
	tmp->infile = find_infile(command_splited);
	tmp->outfile = find_outfile(command_splited);
	tmp->outfile_modes = is_append(command_splited);
	tmp->next = NULL;
	while (*command_splited)
		free(*command_splited++);
	free(command_splited);
}

t_cmd	*parsing_input(t_minishell *minishell, char *input)
{
	t_cmd	*head = NULL;
	t_cmd	*new_cmd = NULL;
	char	**parsed_input;
	int		i;

	if (minishell->cmds)
		delete_cmds(&minishell->cmds);
	parsed_input = split_commands(input, 0, false, false);
	i = 0;
	if (parsed_input[0] && ft_strncmp(parsed_input[0], "|", 1) == 0)
	{
		ft_putstr_fd("Error: invalid command\n", 2);
		free_double_array((void **)parsed_input);
		return (NULL);
	}
	while(parsed_input[i])
	{
		parse_input_help(&new_cmd, parsed_input[i], i, parsed_input);
		append_cmds(&head, new_cmd);
		i += 2;
	}
	free_double_array((void **)parsed_input);
	return (head);
}
