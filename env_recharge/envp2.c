/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 21:02:31 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 21:02:31 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_quotes(char *value)
{
	char	*trimmed_value;

	if ((value[0] == '"' || value[0] == '\'')
		&& value[0] == value[ft_strlen(value) - 1])
	{
		trimmed_value = ft_strndup(value + 1, ft_strlen(value) - 2);
		if (!trimmed_value)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		return (trimmed_value);
	}
	return (value);
}

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(env->name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*create_env_var(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

static bool	is_env_var_null_check(t_minishell *minishell, char *arg, size_t *i)
{
	size_t	start;
	char	*expanded_value;
	char	*value;

	if (arg[*i] == '$')
	{
		start = *i + 1;
		while (arg[start] && (ft_isalnum(arg[start]) || arg[start] == '_'))
			start++;
		if (start == *i + 1)
			return (false);
		expanded_value = ft_strndup(arg + *i + 1, start - *i - 1);
		value = get_env_value(minishell->env_vars, expanded_value, true);
		if (value != NULL)
			return (false);
		*i = start - 1;
	}
	return (true);
}

bool	is_env_var_null(t_minishell *minishell, char *arg)
{
	size_t	i;

	if (arg[0] != '$')
		return (false);
	i = 0;
	while (arg[i])
	{
		if (!is_env_var_null_check(minishell, arg, &i))
			return (false);
		i++;
	}
	return (true);
}
