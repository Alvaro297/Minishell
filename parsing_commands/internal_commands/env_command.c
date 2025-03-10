/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:51 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:51 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int	handle_env(t_cmd *current_cmd, t_minishell *minishell)
{
	t_env	*tmp;
	char	*output;

	output = ft_strdup("");
	tmp = minishell->env_vars;
	while (tmp)
	{
		if (current_cmd->is_pipe)
			output = ft_strjoin_free(output, "%s=%s\n");
		else
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	if (current_cmd->is_pipe)
		minishell->output = output;
	return (0);
}
