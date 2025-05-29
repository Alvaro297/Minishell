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

#include "../../minishell.h"

static void	print_env_error(char *arg)
{
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("’: No such file or directory\n", 2);
}

static void	print_env_vars(t_cmd *current_cmd, t_env *env, char **output)
{
	while (env)
	{
		if (current_cmd->is_pipe)
			*output = ft_strjoin_free(*output, "%s=%s\n");
		else
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

int	handle_env(t_cmd *current_cmd, t_minishell *minishell)
{
	t_env	*tmp;
	char	*output;

	output = ft_strdup("");
	tmp = minishell->env_vars;
	if (!current_cmd->args[1])
	{
		print_env_vars(current_cmd, tmp, &output);
		if (current_cmd->is_pipe)
			minishell->output = ft_strdup(output);
		free(output);
		return (0);
	}
	print_env_error(current_cmd->args[1]);
	free(output);
	return (1);
}
