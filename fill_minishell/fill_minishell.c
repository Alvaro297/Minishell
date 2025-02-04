/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 20:03:50 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-24 20:03:50 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	*fill_mini_expand_variables(char *input, t_minishell *minishell)
{
	char	*trimmed_input;
	bool	in_single_quote;
	bool	in_double_quote;

	trimmed_input = input;
	in_double_quote = false;
	in_single_quote = false;
	while (*trimmed_input == ' ' && trimmed_input)
		trimmed_input++;
	if ((ft_strncmp(trimmed_input, "export", 6) == 0 && (trimmed_input[6] == ' ' || trimmed_input[6] == '\0')) ||
		(ft_strncmp(trimmed_input, "unset", 5) == 0 && (trimmed_input[5] == ' ' || trimmed_input[5] == '\0')) ||
		(ft_strncmp(trimmed_input, "declare", 7) == 0 && (trimmed_input[7] == ' ' || trimmed_input[7] == '\0')))
		return (ft_strdup(trimmed_input));
	else
		return (ft_quote_printf(minishell, *trimmed_input));
}

static void	fill_minishell_help(t_minishell *minishell, char *input, int i)
{
	char	**new_history;
	char	cwd[PATH_MAX];

	new_history = malloc((i + 2) * sizeof(char *));
	if (new_history == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (minishell->history != NULL)
		ft_memcpy(new_history, minishell->history, i * sizeof(char *));
	new_history[i] = ft_strdup(input);
	new_history[i + 1] = NULL;
	free(minishell->history);
	minishell->history = new_history;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		minishell->current_dir = ft_strdup(cwd);
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	minishell->is_interactive = false;
}

void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp)
{
	if (i == 0)
		minishell->env_vars = init_env(envp);
	minishell->input = fill_mini_expand_variables(input, minishell);
	minishell->parsed_input = parsing_input(input, minishell->cmds)
	if (ft_strchr(minishell->input '|') != NULL)
		minishell->pipe = true;
	else
		minishell->pipe = false;
	minishell->second_plane = false;
	minishell->output = NULL;
	minishell->error_message = NULL;
	if (input && *input)
		add_history(input);
	fill_minishell_help(minishell, input, i);
}
