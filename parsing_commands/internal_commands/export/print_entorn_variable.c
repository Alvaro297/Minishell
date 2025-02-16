#include  "../../../minishell.h"

static int	count_nodes(t_env *head)
{
	int	count;

	count = 0;
	while (head) 
	{
		count++;
		head = head->next;
	}
	return (count);
}
static	char *join_all(t_env *sorted_env)
{
	char	*output;

	output = ft_strdup("");
	output = ft_strjoin_free(output, "declare -x ");
	output = ft_strjoin_free(output, sorted_env->name);
	output = ft_strjoin_free(output, "=");
	output = ft_strjoin_free(output, sorted_env->value);
	output = ft_strjoin_free(output, "\n");
	return (output);
}

void	print_entorn_variable(t_minishell *minishell)
{
	char	*output;
	int		count;
	t_env	*env;
	t_env	*sorted_env;

	env = minishell->env_vars;
	sorted_env = NULL;
	count = count_nodes(env);
	if (count > 30)
		sorted_env = merge_sort(env);
	else
		sorted_env = insertion_sort(env);
	while (sorted_env)
	{
		if (minishell->cmds->is_pipe)
			output = join_all(sorted_env);
		else
			printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->value);
		sorted_env = sorted_env->next;
	}
	if (output)
		minishell->output = output;
}
