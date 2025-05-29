/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 17:56:35 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-07 17:56:35 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirected(char *command_splited)
{
	if (ft_strncmp(command_splited, "<", 1) == 0
		|| ft_strncmp(command_splited, ">", 1) == 0
		|| ft_strncmp(command_splited, ">>", 2) == 0
		|| ft_strncmp(command_splited, "<<", 2) == 0)
		return (true);
	return (false);
}

char	*find_command(t_minishell *minishell, char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if (is_redirected(command_splited[i]))
		{
			i++;
			if (!command_splited[i] || is_redirected(command_splited[i]))
				return (NULL);
			i++;
		}
		else if (is_env_var_null(minishell, command_splited[i]))
			i++;
		else
			return (command_splited[i]);
	}
	return (NULL);
}

static char	**find_args_help(t_minishell *minishell,
	char **command_splited, int count)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (command_splited[i])
	{
		if (is_redirected(command_splited[i]))
			i++;
		else if (!is_env_var_null(minishell, command_splited[i]))
		{
			args[j] = ft_strdup(command_splited[i]);
			j++;
		}
		i++;
	}
	args[j] = NULL;
	return (args);
}

char	**find_args(t_minishell *minishell, char **command_splited)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (command_splited[i])
	{
		if (is_redirected(command_splited[i]))
			i++;
		else if (is_env_var_null(minishell, command_splited[i]))
			i++;
		else
			count++;
		if (!command_splited[i])
			break ;
		i++;
	}
	return (find_args_help(minishell, command_splited, count));
}

void	fill_cmd_fields(t_minishell *minishell, t_cmd *tmp,
		char **command_splited, t_parse_data *data)
{
	tmp->cmd = find_command(minishell, command_splited);
	tmp->args = find_args(minishell, command_splited);
	tmp->is_pipe = have_pipe(data->array_commands, data->position);
	tmp->outfile = find_outfile(command_splited);
	tmp->infile = find_infile(command_splited);
	tmp->is_heredoc = is_heredoc(command_splited);
	tmp->here_doc_delim = here_doc_delim(data->command);
	tmp->outfile_array = get_outfiles(command_splited, 0);
	tmp->outfile_modes = is_append(command_splited);
	tmp->next = NULL;
	minishell->heredoc_sd = is_in_sd_quotes(tmp);
	delete_quotes(minishell, tmp);
	printf("Command: %s\n", tmp->cmd);
	for (int i = 0; tmp->args[i]; i++)
	{
		printf("Arg %d: %s\n", i, tmp->args[i]);
	}
}
