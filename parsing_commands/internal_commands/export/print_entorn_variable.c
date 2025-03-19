/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entorn_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:32:08 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:32:08 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../minishell.h"

static t_env *insert_sorted(t_env *sorted_env, t_env *new_node)
{
	t_env *current;

	if (sorted_env == NULL ||
			ft_strncmp(new_node->name, sorted_env->name, ft_strlen(new_node->name)) < 0)
	{
		new_node->next = sorted_env;
		return (new_node);
	}
	current = sorted_env;
	while (current->next != NULL &&
			ft_strncmp(new_node->name, current->next->name, ft_strlen(new_node->name)) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (sorted_env);
}

static t_env *insertion_sort(t_env *env)
{
	t_env *sorted_env = NULL;
	t_env *current;
	t_env *next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		current->next = NULL;
		sorted_env = insert_sorted(sorted_env, current);
		current = next;
	}
	return (sorted_env);
}

static char	*join_all(t_env *sorted_env)
{
	char	*output;

	output = ft_strdup("");
	output = ft_strjoin_free(output, "declare -x ");
	output = ft_strjoin_free(output, sorted_env->name);
	output = ft_strjoin_free(output, "=");
	output = ft_strjoin_free(output, "\"");
	output = ft_strjoin_free(output, sorted_env->value);
	output = ft_strjoin_free(output, "\"");
	output = ft_strjoin_free(output, "\n");
	return (output);
}

void	print_entorn_variable(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*output;
	t_env	*env;
	t_env	*sorted_env;

	env = minishell->env_vars;
	sorted_env = insertion_sort(env);
	while (sorted_env)
	{
		if (current_cmd->is_pipe)
			output = join_all(sorted_env);
		else
			printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->value);
		sorted_env = sorted_env->next;
	}
	if (output)
		minishell->output = output;
}
