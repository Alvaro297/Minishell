# include "../minishell.h"

t_env	*get_env(t_env *env, char *var_name)
{
	size_t len;

	len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->name, var_name, len) == 0 &&
				ft_strlen(env->name) == len)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char *trim_quotes(char *value)
{
	char *trimmed_value;

	if ((value[0] == '"' || value[0] == '\'') && value[0] == value[ft_strlen(value) - 1])
	{
		trimmed_value = ft_strndup(value + 1, ft_strlen(value) - 2);
		if (!trimmed_value)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		return trimmed_value;
	}
	return value;
}

static t_env *find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 &&
			ft_strlen(name) == ft_strlen(env->name))
			return env;
		if (env->next == NULL)
			break;
		env = env->next;
	}
	return env;
}

static t_env *create_env_var(char *name, char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->name = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = NULL;
	return new;
}

void set_env(t_env **env, char *name, char *value)
{
	t_env *tmp;

	value = trim_quotes(value);
	tmp = find_env_var(*env, name);
	if (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
	{
		free(tmp->value);
		tmp->value = value ? ft_strdup(value) : NULL;
		return;
	}
	if (*env == NULL)
		*env = create_env_var(name, value);
	else
		tmp->next = create_env_var(name, value);
}