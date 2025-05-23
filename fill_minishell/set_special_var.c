#include "../minishell.h"

void	set_special_var(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	int		i;
	char	*last_arg;

	last_arg = NULL;
	if (minishell->cmds == NULL)
		return ;
	current_cmd = minishell->cmds;
	while (current_cmd != NULL)
	{
		if (current_cmd->args)
		{
			i = 0;
			while (current_cmd->args[i])
			{
				if (last_arg)
					free(last_arg);
				last_arg = ft_strdup(current_cmd->args[i]);
				i++;
			}
		}
		current_cmd = current_cmd->next;
	}
	if (last_arg)
		set_env(&minishell->env_vars, "_", last_arg);
	else
		set_env(&minishell->env_vars, "_", "");
	if (last_arg)
		free(last_arg);
}
