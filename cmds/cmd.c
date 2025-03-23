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
		free(current->cmd);
		if (current->args)
		{
			for (int i = 0; current->args[i] != NULL; i++)
			{
				free(current->args[i]);
			}
			free(current->args);
		}
		free(current->infile);
		free(current->outfile);
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
