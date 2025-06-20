/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 12:22:42 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-27 12:22:42 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_double_array((void **)cmd->args);
		if (cmd->outfile_array)
			free_double_array((void **)cmd->outfile_array);
		if (cmd->here_doc_delim)
			free_double_array((void **)cmd->here_doc_delim);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}

void	free_all(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->history)
	{
		free_double_array((void **)minishell->history);
	}
	if (minishell->current_dir)
		free(minishell->current_dir);
	if (minishell->input)
		free(minishell->input);
	if (minishell->output)
		free(minishell->output);
	if (minishell->cmds)
		free_cmd_list(minishell->cmds);
	if (minishell->env_vars)
		free_env_list(minishell->env_vars);
	if (minishell->pids)
		free(minishell->pids);
	if (minishell->history_file)
		free(minishell->history_file);
}
