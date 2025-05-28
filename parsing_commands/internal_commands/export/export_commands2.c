/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 15:42:33 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-27 15:42:33 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	export_invalid_identifier(char *arg, char *var_name)
{
	printf("export: `%s': not a valid identifier\n", arg);
	free(var_name);
	return (1);
}

static int	export_set_env(t_minishell *mini, char *var_name, char *var_value)
{
	set_env(&mini->env_vars, var_name, var_value);
	free(var_name);
	return (0);
}

int	export_one_var(t_cmd *cmd, t_minishell *mini, int i)
{
	char	*var_name;
	char	*var_check;

	var_check = ft_strchr(cmd->args[i], '=');
	var_name = parsed_variable_name(cmd->args[i]);
	if (var_check && cmd->args[i][0] != '=')
	{
		var_check++;
		if (parsed_name_validation(var_name)
			&& parsed_value_validation(var_check))
			return (export_set_env(mini, var_name, var_check));
		else
			return (export_invalid_identifier(cmd->args[i], var_name));
	}
	else if (!var_check && var_name)
	{
		if (parsed_name_validation(var_name))
			return (export_set_env(mini, var_name, NULL));
		else
			return (export_invalid_identifier(cmd->args[i], var_name));
	}
	else
		return (export_invalid_identifier(cmd->args[i], var_name));
}
