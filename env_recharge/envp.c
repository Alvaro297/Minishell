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
		new->name = ft_strdup(*envp, sep - *envp);	// Nombre de la variable
		new->value = ft_strdup(sep + 1);			// Valor de la variable
		new->next = head;
		head = new;
		envp++;
	}
	return (head);
}

char *get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return env->value;
		env = env->next;
	}
	return NULL;
}

void	set_env(t_env **env, const char *name, const char *value)
{
	t_env *tmp;
	t_env *new;
	
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	// Si no existe, la agregamos
	*new = malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}
