/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:54:40 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 18:54:40 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_exec(t_exec *e)
{
	int	i;

	if (e->pfd)
	{
		i = 0;
		while (e->pfd[i])
		{
			free(e->pfd[i]);
			e->pfd[i] = NULL;
			i++;
		}
		free(e->pfd);
		e->pfd = NULL;
	}
	if (e->heredoc_fds)
	{
		free(e->heredoc_fds);
		e->heredoc_fds = NULL;
	}
	if (e->pids)
	{
		free(e->pids);
		e->pids = NULL;
	}
}
