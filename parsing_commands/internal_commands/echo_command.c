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

	echo_print = ft_strdup("");
	while (minishell->cmds->args[i] != NULL)
	{
		echo_print = ft_strjoin_free(echo_print, minishell->cmds->args[i]);
		if (minishell->cmds->args[i + 1] != NULL)
			echo_print = ft_strjoin_free(echo_print, " ");
		i++;
	}
	if (newline)
		echo_print = ft_strjoin_free(echo_print, "\n");
	if (minishell->cmds->is_pipe)
		minishell->output = echo_print;
	else
		printf("%s", echo_print);
}

int	handle_echo(t_minishell *minishell)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (minishell->input != NULL &&
			ft_strncmp(minishell->cmds->args[i], "-n", 2) == 0 &&
			ft_strlen(minishell->cmds->args[i]) == 2)
	{
		i++;
		newline = 0;
	}
	while (minishell->cmds->args[i] != NULL)
	{
		printf("%s", minishell->cmds->args[i]);
		if (minishell->cmds->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
