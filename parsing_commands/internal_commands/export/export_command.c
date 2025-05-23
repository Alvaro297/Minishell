/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:32:15 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:32:15 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../minishell.h"

static char	*parsed_variable_name(char *str)
{
	char	*equal_pos;
	char	*var_name;
	size_t	name_len;
	
	equal_pos = ft_strchr(str, '=');
	if (equal_pos != NULL) {
		name_len =equal_pos - str + 1;
		var_name = malloc(name_len + 1);
		if (!var_name)
			return (NULL);
		ft_strlcpy(var_name, str, name_len);
		var_name[name_len] = '\0';
	}
	else if (str)
		var_name = ft_strdup(str);
	else
		var_name = NULL;
//	printf("VAR NAME: %s\n", var_name);
return (var_name);
}

static bool parsed_value_validation(char *var_value)
{
	int i;
	int j;

	i = 0;
	if (ft_isdigit(var_value[i]))
		return (false);
	if ((var_value[i] == '\'' && var_value[ft_strlen(var_value) - 1] == '\'') ||
		(var_value[i] == '"' && var_value[ft_strlen(var_value) - 1] == '"'))
		return (true);
	else
	{
		while (var_value[i])
		{
			j = 0;
			while (INVALID_CHARACTERSV[j])
			{
				if (INVALID_CHARACTERSV[j] == var_value[i])
					return (false);
				j++;
			}
			i++;
		}
	}
	return (true);
}

static bool parsed_name_validation(char *var_name)
{
	int i;
	int j;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (false);
	while (var_name[i])
	{
		j = 0;
		while (INVALID_CHARACTERS[j])
		{
			if (INVALID_CHARACTERS[j] == var_name[i])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static int	export_one_var(t_cmd *cmd, t_minishell *mini, int i)
{
	char *var_name;
	char *var_check;
	
	var_check = ft_strchr(cmd->args[i], '=');
	var_name = parsed_variable_name(cmd->args[i]);
	if (var_check && cmd->args[i][0] != '=')
	{
		var_check++;
		if (parsed_name_validation(var_name)
			&& parsed_value_validation(var_check))
			set_env(&mini->env_vars, var_name, var_check);
		else
			return (printf("export: `%s': not a valid identifier\n", cmd->args[i]), free(var_name), 1);
	}
	else if (!var_check && var_name)
	{
		if (parsed_name_validation(var_name))
			set_env(&mini->env_vars, var_name, NULL);
		else
			return (printf("export: `%s': not a valid identifier\n", cmd->args[i]), free(var_name), 1);
	}
	else
		return (printf("export: `%s': not a valid identifier\n", cmd->args[i]), free(var_name), 1);
	free(var_name);
	return (0);
}

int	handle_export(t_cmd *cmd, t_minishell *mini)
{
	int i = 0, ret = 0;
	while (cmd->args[++i])
		if ((ret = export_one_var(cmd, mini, i)))
			return (ret);
	if (cmd->is_pipe && cmd->args[1])
		mini->output = ft_strdup("");
	if (!mini->cmds->args[1])
		print_entorn_variable(cmd, mini);
	return (0);
}
