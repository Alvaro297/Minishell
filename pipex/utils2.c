/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:31:00 by paperez-          #+#    #+#             */
/*   Updated: 2025/05/29 18:31:22 by paperez-         ###   ########.fr       */
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

void	free_pipe_fds(int **pfd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}

int	count_envs(t_env *env)
{
	t_env	*iter;
	int		count;

	iter = env;
	count = 0;
	while (iter)
	{
		count++;
		iter = iter->next;
	}
	return (count);
}

char	**returntoenvp(t_env *env)
{
	char	**envchar;
	char	*tmp;
	int		count;

	envchar = NULL;
	tmp = NULL;
	count = count_envs(env);
	envchar = malloc(sizeof(char *) * (count + 1));
	if (!envchar)
		return (NULL);
	count = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		envchar[count] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		count++;
	}
	envchar[count] = NULL;
	return (envchar);
}
