/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 18:54:40 by alvamart          #+#    #+#             */
/*   Updated: 2025/06/03 18:32:01 by paperez-         ###   ########.fr       */
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

void	free_exec(t_exec *e, t_minishell *minishell)
{
	int	i;

	if (e->pfd)
	{
		i = 0;
		while (i < minishell->howmanycmd - 1)
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

void	free_exec_builtin(t_exec *e, t_minishell *minishell)
{
	int	i;

	if (e->pfd)
	{
		i = 0;
		while (i < minishell->howmanycmd - 1)
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
		while (e->j < minishell->howmanyhd)
		{
			close(e->heredoc_fds[e->j]);
			e->j++;
		}
		free(e->heredoc_fds);
		e->heredoc_fds = NULL;
	}
	if (e->pids)
	{
		free(e->pids);
		e->pids = NULL;
	}
}

void	closestd(t_minishell *minishell)
{
	close(minishell->std_in);
	close(minishell->std_out);
}
