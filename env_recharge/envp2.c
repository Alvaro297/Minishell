# include "../minishell.h"

t_env	*get_env(t_env *env, const char *var_name)
{
	size_t len;

	len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->name, var_name, j) == 0 &&
				(int)ft_strlen(env->name) == j)
			return (env);
		env = env->next;
	}
	return (NULL);
}