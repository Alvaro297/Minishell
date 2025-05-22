/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 18:07:47 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-07 18:07:47 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	delete_cmds(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
			free_double_array((void **) current->args);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->outfile_array)
			free_double_array((void **) current->outfile_array);
		free(current);
		current = next;
	}
	cmd = NULL;
}
void	append_cmds(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd *current;

	if (*cmds == NULL)
		*cmds = new_cmd;
	else
	{
		current = *cmds;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}
