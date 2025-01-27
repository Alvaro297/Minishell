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

void	fill_minishell(char *input, t_minishell *minishell, int i, char **envp)
{
	char	**new_history;

	minishell->input = input;
	minishell->parsed_input = ft_split(input, ' ');
	if (ft_strchr(minishell->input '|') != NULL)
		minishell->pipe = true;
	else
		minishell->pipe = false;
	minishell->second_plane = false;
	minishell->output = NULL;
	minishell->error_message = NULL;
	if (input && *input)
		add_history(input);
	new_history = malloc((i + 2) * sizeof(char *))
	if (minishell->history != NULL)
		ft_memcpy(new_history, minishell->history, i * sizeof(char *));
	new_history[i] = ft_strdup(input);
	new_history[i + 1] = NULL;
	free(minishell->history);
	minishell->history = new_history;
	minishell->env_vars = envp;
	minishell->current_dir = getcwd();
	minishell->is_interactive = false;
}
