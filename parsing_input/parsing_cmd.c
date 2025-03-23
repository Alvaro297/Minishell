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
    cmd->next = NULL;
}

static void	parse_input_help(t_cmd **new_cmd, char *command, int position, char **array_commands)
{
	t_cmd	*tmp;
	char	**command_splited;
	int		i;
	
	tmp = malloc(sizeof(t_cmd));
	init_cmd(tmp); 
	*new_cmd = tmp;
	command_splited = split_modified(command, ' ');
	tmp->cmd = find_command(command_splited);
	tmp->args = find_args(command_splited); 
	tmp->is_pipe = have_pipe(array_commands, position);
	tmp->infile = find_infile(command_splited);
	tmp->outfile = find_outfile(command_splited);
	tmp->outfile_array = get_outfiles(command_splited);
	tmp->outfile_modes = is_append(command_splited);
	tmp->next = NULL;
	delete_quotes(tmp);
	i = 0;
	while (command_splited[i] != NULL)
	{
		free(command_splited[i]);
		i++;
	}
	free(command_splited);//FUNCIONA CORRECTAMENTE
}

t_cmd	*parsing_input(t_minishell *minishell, char *input)
{
	t_cmd		*head = NULL;
	t_cmd		*new_cmd = NULL;
	char		**parsed_input;
	int			i;
	t_quotes	quotes;

	if (minishell->cmds)
		delete_cmds(minishell->cmds);
	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	parsed_input = split_commands(input, 0, &quotes);
	if (parsed_input) {
    int j = 0;
    printf("split_commands returned:\n");
    while (parsed_input[j]) {
        printf("parsed_input[%d]: %s\n", j, parsed_input[j]);
        j++;
    }
	} else {
    	printf("split_commands returned NULL\n");
	}
	i = 0;
	if (parsed_input[0] && ft_strncmp(parsed_input[0], "|", 1) == 0)
	{
		free_double_array((void **)parsed_input);
		return (NULL);
	}
	while(parsed_input[i])
	{
		parse_input_help(&new_cmd, parsed_input[i], i, parsed_input);
		append_cmds(head, new_cmd);
		printf("Iteration %d: appended command '%s'\n", i, parsed_input[i]);
		i += 2;
	}
	return (head);//FUNCIONA BIEN
}
