# include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env *head = NULL;
	t_env *new;
	char *sep;
	
	while (*envp)
	{
		if (ft_strncmp(*envp, "_=", 2) != 0)
		{
					
			new = malloc(sizeof(t_env));
			sep = ft_strchr(*envp, '=');
			if (!new || !sep)
				return NULL;
			new->name = ft_strndup(*envp, sep - *envp);	// Nombre de la variable
			new->value = ft_strdup(sep + 1);			// Valor de la variable
			new->next = head;
			head = new;
		}
		envp++;
	}
	return (head);
}

char	*get_env_value(t_env *env, char *var_name)
{
	int j;
	
	j = 0;
	while (var_name[j] != ' ' && var_name[j] != '\t' && var_name[j] != '\0')
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

void	set_env(t_env **env, char *name, char *value)
{
	t_env *tmp;
	t_env *new;
	
	new = malloc(sizeof(t_env));
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0 &&
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
	new->name = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
		tmp->next = new;
}

static void	delete_env_help(t_env *prev, t_env *tmp, char *name)
{
	t_env *to_free;

	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0 &&
				ft_strlen(name) == ft_strlen(tmp->name))
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
	if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0 &&
				ft_strlen(name) == ft_strlen(tmp->name))
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	else
		delete_env_help(tmp, tmp->next, name);
}
