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
