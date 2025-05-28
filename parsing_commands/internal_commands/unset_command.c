/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:41 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:41 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_unset(t_cmd *current_cmd, t_minishell *minishell)
{
	int	i;

	i = 1;
	while (current_cmd->args[i])
	{
		delete_env(&minishell->env_vars, current_cmd->args[i]);
		i++;
	}
	return (0);
}
