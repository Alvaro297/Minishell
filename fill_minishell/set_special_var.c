#include "../minishell.h"

void	set_special_var_inputNull(t_minishell *minishell, char *result)
{
	char	**command_splited;
	int		i;
	char	*last_arg;

	command_splited = split_modified(result, ' ');
	command_splited = process_redirection(command_splited);
	last_arg = NULL;
	if (command_splited == NULL)
		return ;
	i = 0;
	while (command_splited[i])
	{
		if (last_arg)
			free(last_arg);
		last_arg = ft_strdup(command_splited[i]);
		i++;
	}
	set_env(&minishell->env_vars, "_", last_arg);
	if (last_arg)
		free(last_arg);
	free_double_array((void **)command_splited);
}

void	set_special_var(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	int		i;
	char	*last_arg;

	last_arg = NULL;
	if (minishell->cmds == NULL || minishell->input == NULL)
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
