/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 20:13:45 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 20:13:45 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_minishell *minishell)
{
	int	c;

	c = 0;
	while (minishell->cmds->args[c])
	{
		free(minishell->cmds->args[c]);
		c++;
	}
	free(minishell->cmds->args);
	free(minishell->cmds->infile);
	free(minishell->cmds->outfile);
	free(minishell->cmds->cmd);
	free(minishell->cmds->args);
	free(minishell->input);
	free(minishell->pids);
	free(minishell->output);
	printf("error");
}
