/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_special_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:55:58 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 18:55:58 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_special_var_input_null(t_minishell *minishell, char *result)
{
	char	**command_splited;
	int		i;
	char	*last_arg;

	command_splited = split_modified(result, ' ');
	command_splited = process_redirection(command_splited);
	last_arg = NULL;
	if (command_splited == NULL)
		return ;
	i = 0;
	while (command_splited[i])
	{
		if (last_arg)
			free(last_arg);
		last_arg = ft_strdup(command_splited[i]);
		i++;
	}
	set_env(&minishell->env_vars, "_", last_arg);
	if (last_arg)
		free(last_arg);
	free_double_array((void **)command_splited);
}

static void	set_last_arg_env(t_minishell *minishell, char *last_arg)
{
	if (last_arg)
		set_env(&minishell->env_vars, "_", last_arg);
	else
		set_env(&minishell->env_vars, "_", NULL);
	if (last_arg)
		free(last_arg);
}

void	set_env_ask(t_minishell *minishell, int g_signal_now)
{
	char	*ask_value;

	if (g_signal_now == 130)
	{
		ask_value = ft_itoa(g_signal_now);
		set_env(&minishell->env_vars, "?", ask_value);
		free(ask_value);
		g_signal = 0;
	}
}

void	set_special_var(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	int		i;
	char	*last_arg;

	last_arg = NULL;
	if (minishell->cmds == NULL || minishell->input == NULL)
		return ;
	current_cmd = minishell->cmds;
	while (current_cmd != NULL)
	{
		if (current_cmd->args)
		{
			i = 0;
			while (current_cmd->args[i])
			{
				if (last_arg)
					free(last_arg);
				last_arg = ft_strdup(current_cmd->args[i]);
				i++;
			}
		}
		current_cmd = current_cmd->next;
	}
	set_last_arg_env(minishell, last_arg);
	set_env_ask(minishell, g_signal);
}
