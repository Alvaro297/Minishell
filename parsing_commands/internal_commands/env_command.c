/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:51 by alvamart          #+#    #+#             */
/*   Updated: 2025/06/10 19:20:47 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_env_error(char *arg)
{
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
}

static void	print_env_vars(t_env *env)
{
	while (env)
	{
		if (env->value[0] != '\0')
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

int	handle_env(t_cmd *current_cmd, t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env_vars;
	if (!current_cmd->args[1])
	{
		print_env_vars(tmp);
		return (0);
	}
	print_env_error(current_cmd->args[1]);
	return (1);
}
