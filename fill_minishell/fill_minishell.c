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

bool	is_in_sd_quotes(t_cmd *cmds)
{
	t_cmd	*current_cmd;
	int		i;
	bool	inside_quotes;

	current_cmd = cmds;
	inside_quotes = false;
	while (current_cmd != NULL)
	{
		if (current_cmd->is_heredoc && current_cmd->here_doc_delim)
		{
			i = 0;
			while (current_cmd->here_doc_delim[i])
			{
				if (current_cmd->here_doc_delim[i][0] == '\''
						&& current_cmd->here_doc_delim[i]
						[ft_strlen(current_cmd->here_doc_delim[i]) - 1] == '\'')
					inside_quotes = true;
				else
					inside_quotes = false;
				i++;
			}
		}
		current_cmd = current_cmd->next;
	}
	return (inside_quotes);
}

static void	fill_minishell_help(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*previous_pwd;

	minishell->output = NULL;
	minishell->howmanycmd = howmanycmds(minishell->cmds);
	previous_pwd = minishell->current_dir;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		minishell->current_dir = ft_strdup(cwd);
	else
	{
		perror("minishell: warning: getcwd failed");
		if (previous_pwd)
			minishell->current_dir = ft_strdup(previous_pwd);
		else
			minishell->current_dir = ft_strdup("");
	}
	if (previous_pwd)
		free(previous_pwd);
}

void	fill_minishell(char *input, t_minishell *minishell, char **envp)
{
	if (minishell->env_vars == NULL && *envp != NULL)
		minishell->env_vars = init_env(envp);
	else if (*envp == NULL && minishell->env_vars == NULL)
		minishell->env_vars = init_env_without_env();
	minishell->input = ft_quote_printf(minishell, input, true);
	if (input && *input && ft_strrchr(input, '\n') == NULL)
	{
		set_special_var(minishell);
		add_history(input);
		add_to_history(minishell, input);
	}
	if (minishell->input == NULL)
	{
		if (minishell->cmds)
		{
			free_cmd_list(minishell->cmds);
			minishell->cmds = NULL;
		}
		return ;
	}
	minishell->cmds = parsing_input(minishell, input);
	if (minishell->cmds == NULL)
		return ;
	fill_minishell_help(minishell);
}
