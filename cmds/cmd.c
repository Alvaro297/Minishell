# include "../minishell.h"

void	delete_cmds(t_env *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *cmds;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd);
		if (current->args)
		{
			for (int i = 0; current->args[i] != NULL; i++)
			{
				free(current->args[i]);
			}
			free(current->args);
		}
		free(current->infile);
		free(current->outfile);
		free(current);
		current = next;
	}
	*cmds = NULL;
}
void append_cmds(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd *current;

	if (*cmds == NULL)
	{
		*cmds = new_cmd;
	}
	else
	{
		current = *cmds;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_cmd;
	}
}