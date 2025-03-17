# include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env *head = NULL;
	t_env *new;
	char *sep;
	
	while (*envp)
	{
		new = malloc(sizeof(t_env));
		sep = ft_strchr(*envp, '=');
		if (!new || !sep)
			return NULL;
		new->name = ft_strndup(*envp, sep - *envp);	// Nombre de la variable
		new->value = ft_strdup(sep + 1);			// Valor de la variable
		new->next = head;
		head = new;
		envp++;
	}
	return (head);
}
char	*get_env_value(t_env *env, const char *var_name)
{
	int i;
	int j;
	size_t len;
	
	j = 0;
	i = 0;
	len = ft_strlen(var_name);
	while (var_name[j] != ' ' && var_name[j] != '\t' && var_name)
		j++;
	while (env)
	{
		if (ft_strncmp(env->name, var_name, j) == 0 &&
				(int)ft_strlen(env->name) == j)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env(t_env **env, const char *name, const char *value)
{
	t_env *tmp;
	t_env *new;
	
	tmp = *env;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->name, name) == 0 &&
			ft_strlen(name) == ft_strlen(tmp->name))
		{
			free(tmp->value);
			new->value = value ? ft_strdup(value) : NULL;
			return ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
		tmp->next = new;
}

static void	delete_env_help(t_env **env, t_env *prev, t_env *tmp, const char *name)
{
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->name, name, ft_strlen(name)) == 0 &&
				ft_strlen(name) == ft_strlen(tmp->name))
		{
			prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		if (tmp->next == NULL)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	delete_env(t_env **env, const char *name)
{
	t_env	*tmp;

	tmp = *env;
	if (ft_strcmp(tmp->name, name, ft_strlen(name)) == 0 &&
				ft_strlen(name) == ft_strlen(tmp->name))
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	else
		delete_env_help(env, tmp, tmp->next, name);
}
