/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 12:59:39 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-27 12:59:39 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

int	howmanycmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*env_to_str(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->name, "=");
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

char	**returntoenvp(t_env *env)
{
	char	**envchar;
	int		count;
	int		i;

	count = env_list_size(env);
	envchar = malloc(sizeof(char *) * (count + 1));
	if (!envchar)
		return (NULL);
	i = 0;
	while (env)
	{
		envchar[i] = env_to_str(env);
		env = env->next;
		i++;
	}
	envchar[i] = NULL;
	return (envchar);
}
