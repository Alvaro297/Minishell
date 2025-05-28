/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:49:41 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 18:49:41 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_minishell(t_minishell *minishell)
{
	minishell->env_vars = NULL;
	minishell->history = NULL;
	minishell->current_dir = NULL;
	minishell->input = NULL;
	minishell->cmds = NULL;
	minishell->output = NULL;
	minishell->pids = NULL;
	minishell->history_file = get_history_file();
	minishell->heredoc_sd = false;
	minishell->howmanycmd = 0;
	minishell->last_exit_status = 0;
}

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->is_pipe = false;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->outfile_array = NULL;
	cmd->is_heredoc = false;
	cmd->here_doc_delim = NULL;
	cmd->outfile_modes = 0;
	cmd->next = NULL;
}
