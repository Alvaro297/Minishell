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