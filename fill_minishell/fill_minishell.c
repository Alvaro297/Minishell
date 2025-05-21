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

void	fill_minishell(char *input, t_minishell *minishell, char **envp)
{
	char	*tmp;

	if (minishell->env_vars == NULL)
		minishell->env_vars = init_env(envp);
	minishell->input = ft_quote_printf(minishell, input);
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
		free_double_array((void **) minishell->here_doc_delim);
	minishell->here_doc_delim = here_doc_delim(minishell->input);
	if (minishell->here_doc_delim)
		minishell->here_doc_delim = delete_quotes_double_array(minishell, cmd->here_doc_delim, false);
	if (input && *input)
	{
		add_history(input);
		add_to_history(minishell, input);
	}
	fill_minishell_help(minishell);
}
