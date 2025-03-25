#include "pipex.h"
#include "../minishell.h"

int howmanycmds(t_cmd *cmd)
{
	t_cmd	**tmp;
	int		i;
	
	i = 0;
	tmp = (t_cmd **)malloc(sizeof(t_cmd));
	while (cmd)
	{
		tmp[i] = cmd;
		cmd = cmd->next;
		i++;
	}
	cmd = tmp[0];
	return (i);
}

char	**returntoenvp(t_env *env)
{
	char	**envchar;
	t_env	**tmp;
	int			i;

	envchar = (char **)malloc(sizeof(char *));
	tmp = (t_env **)malloc(sizeof(t_env));
	i = 0;
	while (env)
	{
		envchar[i] = ft_calloc(0, sizeof(char) * (ft_strlen(env->name + ft_strlen(env->value) + 2)));
		envchar[i] = ft_strjoin(env->name, "=");
		envchar[i] = ft_strjoin(envchar[i], env->value);
		tmp[i] = env;
		env = env->next;
		i++;
	}
	envchar[i] = NULL;
	env = tmp[0];
	return (envchar);
}
