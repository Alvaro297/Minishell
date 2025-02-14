# include "../../minishell.h"

int	handle_unset(t_minishell *minishell)
{
	int		i;
	bool	is_var_readonly;

	i = 1;
	is_var_readonly = false;
	while (minishell->cmds->args[i])
	{
		if (!is_readonly(minishell->cmds->args[i]))
			delete_env(&minishell->env_vars, minishell->cmds->args[i]);
		else
		{
			write(2, "minishell: unset: %s: cannot unset: readonly variable\n", 55);
			is_var_readonly = 1;
		}
	}
	if (is_var_readonly)
		return (1);
	else
		return (0);
}
