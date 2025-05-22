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

#include "../minishell.h"

static void	fill_minishell_help(t_minishell *minishell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (minishell->current_dir)
			free(minishell->current_dir);
		minishell->current_dir = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
}

bool	is_in_sd_quotes(char **here_doc_delim)
{
	int	i;

	i = 0;
	while (here_doc_delim[i])
		i++;
	if (i != 0 && here_doc_delim[i - 1][0] == '\''
			&& here_doc_delim[i - 1][ft_strlen(here_doc_delim[i - 1]) - 1] == '\'')
	{
		return (true);
	}
	return (false);
}

void	fill_minishell(char *input, t_minishell *minishell, char **envp)
{
	if (minishell->env_vars == NULL)
		minishell->env_vars = init_env(envp);
	minishell->input = ft_quote_printf(minishell, input, true);
	if (minishell->input == NULL)
	{
		if (minishell->cmds)
		{
			free_cmd_list(minishell->cmds);
			minishell->cmds = NULL;
		}
		free(input);
		return ;
	}
	minishell->cmds = parsing_input(minishell, input);
	minishell->output = NULL;
	minishell->howmanycmd = howmanycmds(minishell->cmds);
	if (minishell->here_doc_delim)
	{
		free_double_array((void **) minishell->here_doc_delim);
		minishell->here_doc_delim = NULL;
	}
	minishell->here_doc_delim = here_doc_delim(input);
	minishell->heredoc_sd = is_in_sd_quotes(minishell->here_doc_delim);
	if (minishell->here_doc_delim)
		minishell->here_doc_delim = delete_quotes_double_array(minishell, minishell->here_doc_delim, false);
	if (input && *input)
	{
		add_history(input);
		add_to_history(minishell, input);
	}
	fill_minishell_help(minishell);
}
