/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 15:29:52 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 15:29:52 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_shlvl(void)
{
	char	*shlvl;
	int		shlvl_value;

	shlvl = getenv("SHLVL");
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		return (ft_itoa(shlvl_value));
	}
	return (ft_strdup("1"));
}

t_env	*get_env(t_env *env, char *var_name)
{
	size_t	len;

	len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->name, var_name, len) == 0
			&& ft_strlen(env->name) == len)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	update_env_value(t_env *tmp, char *value)
{
	if (tmp->value)
		free(tmp->value);
	if (value)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
}

void	set_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*last;

	last = NULL;
	tmp = find_env_var(*env, name);
	if (!(name && value && ft_strcmp(name, "_") == 0
			&& ((value[0] == '"' && value[1] == '\0')
				|| (value[0] == '\'' && value[1] == '\0'))))
		value = trim_quotes(value);
	if (tmp)
	{
		update_env_value(tmp, value);
		return ;
	}
	if (*env == NULL)
		*env = create_env_var(name, value);
	else
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = create_env_var(name, value);
	}
}

t_env	*init_env_without_env(void)
{
	t_env	*head;
	char	cwd[1024];

	head = NULL;
	set_env(&head, "SHLVL", init_shlvl());
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env(&head, "PWD", cwd);
		set_env(&head, "OLDPWD", cwd);
	}
	set_env(&head, "HOME", "/");
	set_env(&head, "PATH", "");
	set_env(&head, "_", "");
	set_env(&head, "?", "0");
	return (head);
}
