/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 21:13:17 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 21:13:17 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	*sep;
	char	*var_value;

	head = NULL;
	while (*envp)
	{
		new = malloc(sizeof(t_env));
		sep = ft_strchr(*envp, '=');
		if (!new || !sep)
			return (NULL);
		new->name = ft_strndup(*envp, sep - *envp);
		new->value = ft_strdup(sep + 1);
		new->next = head;
		head = new;
		envp++;
	}
	var_value = ft_itoa(g_signal);
	set_env(&head, "?", ft_strdup(var_value));
	free(var_value);
	var_value = init_shlvl();
	set_env(&head, "SHLVL", var_value);
	free(var_value);
	return (head);
}

char	*get_env_value(t_env *env, char *var_name, bool free_var)
{
	int	j;

	j = 0;
	while (var_name[j] != ' ' && var_name[j] != '\t' && var_name[j] != '\0')
		j++;
	while (env)
	{
		if (ft_strncmp(env->name, var_name, j) == 0
			&& (int)ft_strlen(env->name) == j)
		{
			if (free_var)
				free(var_name);
			return (env->value);
		}
		env = env->next;
	}
	if (free_var)
		free(var_name);
	return (NULL);
}

static void	delete_env_help(t_env *prev, t_env *tmp, char *name)
{
	t_env	*to_free;

	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(tmp->name))
		{
			if (prev)
				prev->next = tmp->next;
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->name);
			free(to_free->value);
			free(to_free);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	delete_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0
		&& ft_strlen(name) == ft_strlen(tmp->name))
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	else
		delete_env_help(tmp, tmp->next, name);
}
