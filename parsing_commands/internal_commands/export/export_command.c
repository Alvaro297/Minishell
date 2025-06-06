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

#include "../../../minishell.h"

char	*parsed_variable_name(char *str)
{
	char	*equal_pos;
	char	*var_name;
	size_t	name_len;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos != NULL)
	{
		name_len = equal_pos - str + 1;
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
	return (var_name);
}

bool	parsed_name_validation(char *var_name)
{
	int	i;
	int	j;

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

int	handle_export(t_cmd *cmd, t_minishell *mini)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd->args[++i])
	{
		ret = export_one_var(cmd, mini, i);
		if (ret)
			return (ret);
	}
	if (!mini->cmds->args[1])
		print_entorn_variable(mini);
	return (0);
}
