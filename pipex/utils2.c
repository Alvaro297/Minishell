#include "pipex.h"
#include "../minishell.h"

int howmanycmds(t_cmd *cmd)
{
	int	count;

	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
