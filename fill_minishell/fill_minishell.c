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

static void	fill_minishell_help(t_minishell *minishell, char *input, int i)
{
	char	cwd[PATH_MAX];
	
	minishell->history = ft_realloc(minishell->history, (i + 2) * sizeof(char *));
	if (minishell->history == NULL)
	{
		perror("ft_realloc");
		exit(EXIT_FAILURE);
	}
	minishell->history[i] = ft_strdup(input);
	minishell->history[i + 1] = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		minishell->current_dir = ft_strdup(cwd);
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
}

void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp)
{
	t_cmd	*tmp_cmd;
	if (minishell->env_vars == NULL)
		minishell->env_vars = init_env(envp);
	minishell->input = ft_quote_printf(minishell, input);
	printf("%s\n", minishell->input);
	minishell->cmds = parsing_input(minishell, minishell->input);
	tmp_cmd = minishell->cmds;
	while (tmp_cmd)
	{
		printf("%s", tmp_cmd->cmd);
		tmp_cmd  = tmp_cmd->next;
	}
	minishell->output = NULL;
	minishell->howmanycmd = howmanycmds(minishell->cmds);
	if (input && *input)
	{
		add_history(input);
		add_to_history(minishell, input);
	}
	fill_minishell_help(minishell, input, i);
}
