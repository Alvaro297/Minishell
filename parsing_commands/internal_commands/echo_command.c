/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:56 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:56 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_echo_help(t_minishell *minishell, int i, int newline)
{
	char	*echo_print;
	t_cmd	*current_cmd;

	current_cmd = minishell->cmds;
	echo_print = ft_strdup("");
	while (current_cmd->args[i] != NULL)
	{
		echo_print = ft_strjoin_free(echo_print, current_cmd->args[i]);
		if (current_cmd->args[i + 1] != NULL)
			echo_print = ft_strjoin_free(echo_print, " ");
		i++;
	}
	if (newline)
		echo_print = ft_strjoin_free(echo_print, "\n");
	while (echo_print)
	{
		write(STDOUT_FILENO, &echo_print, 1);
		echo_print++;
	}
}

static void	print_echo_args(t_cmd *current_cmd, int i)
{
	int	j;

	while (current_cmd->args[i] != NULL)
	{
		j = 0;
		while (current_cmd->args[i][j] != '\0')
		{
			write(STDOUT_FILENO, &current_cmd->args[i][j], 1);
			j++;
		}
		if (current_cmd->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

int	handle_echo(t_cmd *current_cmd, t_minishell *minishell)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (minishell->input != NULL
		&& ft_strncmp(current_cmd->args[i], "-n", 2) == 0
		&& ft_strlen(current_cmd->args[i]) == 2)
	{
		i++;
		newline = false;
	}
	print_echo_args(current_cmd, i);
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
