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

# include "../../minishell.h"

int	handle_unset(t_cmd *current_cmd, t_minishell *minishell)
{
	int		i;
	bool	is_var_readonly;

	i = 1;
	is_var_readonly = false;
	while (current_cmd->args[i])
	{
		if (!is_readonly(minishell, current_cmd->args[i]))
			delete_env(&minishell->env_vars, current_cmd->args[i]);
		else
		{
			write(2, "minishell: unset: %s: cannot unset: readonly variable\n", 55);
			is_var_readonly = 1;
		}
	}
	if (is_var_readonly)
		return (1);
	else
		return (0);
}
