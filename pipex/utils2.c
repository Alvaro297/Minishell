#include "pipex.h"
#include "../minishell.h"

int	howmanycmds(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	free_pipe_fds(int **pfd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}

char	**returntoenvp(t_env *env)
{
	char	**envchar;
	int		count;
	int		i;
	char	*tmp;

	count = 0;
	t_env *iter = env;
	while (iter)
	{
		count++;
		iter = iter->next;
	}
	envchar = malloc(sizeof(char *) * (count + 1));
	if (!envchar)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		envchar[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	envchar[i] = NULL;
	return (envchar);
}
