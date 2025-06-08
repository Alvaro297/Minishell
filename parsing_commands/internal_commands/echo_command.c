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

static int	print_echo_args(t_cmd *current_cmd, int i)
{
	int		j;
	ssize_t	ret;

	while (current_cmd->args[i] != NULL)
	{
		j = 0;
		while (current_cmd->args[i][j] != '\0')
		{
			ret = write(STDOUT_FILENO, &current_cmd->args[i][j], 1);
			if (ret == -1 && errno == EPIPE)
				return (1);
			j++;
		}
		if (current_cmd->args[i + 1] != NULL)
		{
			ret = write(STDOUT_FILENO, " ", 1);
			if (ret == -1 && errno == EPIPE)
				return (1);
		}
		i++;
	}
	return (0);
}

int	handle_echo(t_cmd *current_cmd, t_minishell *minishell)
{
	int		i;
	int		j;
	bool	newline;
	int		ret;

	i = 1;
	j = 1;
	ret = 0;
	newline = true;
	if (minishell->input != NULL && current_cmd->args[i] != NULL
		&& ft_strncmp(current_cmd->args[i], "-", 1) == 0)
	{
		while (current_cmd->args[i][j] == 'n')
			j++;
		if (current_cmd->args[i][j] == '\0')
		{
			newline = false;
			i++;
		}
	}
	ret = print_echo_args(current_cmd, i);
	if (newline && ret == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (ret);
}
