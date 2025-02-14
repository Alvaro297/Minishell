# include "../../minishell.h"

int	handle_env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env_vars;
	while (tmp)
	{
		printf("%s=%s", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
