/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-29 10:55:54 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-29 10:55:54 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	ft_isnum(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	exit_with_code(t_minishell *minishell, int code)
{
	free_all(minishell);
	closestd(minishell);
	exit((unsigned char)code);
}

int	handle_exit(t_cmd *cmd, t_minishell *minishell)
{
	int	code;
	int	argc;

	code = 0;
	argc = 0;
	while (cmd->args[argc])
		argc++;
	if (argc == 1)
	{
		printf("exit\n");
		exit_with_code(minishell, 0);
	}
	if (argc == 2)
	{
		if (!ft_isnum(cmd->args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_with_code(minishell, 2);
		}
		code = ft_atoi(cmd->args[1]);
		exit_with_code(minishell, code);
	}
	if (argc > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	return (0);
}
