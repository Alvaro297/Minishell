# include "../minishell.h"

bool	is_readonly(t_minishell *minishell, char *var)
{
	t_env *env;

	env = get_env(minishell, var);
	if (env && env->is_readonly == 0)
		return (false);
	return (true);
}

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