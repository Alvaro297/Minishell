# include "../../minishell.h"

int	handle_env(t_minishell *minishell)
{
	t_env	*tmp;
	char	*output;

	output = ft_strdup("");
	tmp = minishell->env_vars;
	while (tmp)
	{
		if (minishell->cmds->is_pipe)
			ft_strjoin(output, "%s=%s\n");
		else
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	if (minishell->cmds->is_pipe)
		minishell->output = output;
	return (0);
}
