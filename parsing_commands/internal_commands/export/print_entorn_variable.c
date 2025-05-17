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
	output = ft_strjoin_free(output, "\'");
	output = ft_strjoin_free(output, sorted_env->value);
	output = ft_strjoin_free(output, "\'");
	output = ft_strjoin_free(output, "\n");
	return (output);
}

static t_env *duplicate_env_list(t_env *env)
{
	t_env *new_list = NULL;
	t_env *current = env;
	t_env *new_node;
	t_env *last = NULL;

	while (current)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(current->name);
		new_node->value = ft_strdup(current->value);
		new_node->next = NULL;
		if (!new_list)
			new_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		current = current->next;
	}
	return (new_list);
}

void	print_entorn_variable(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*output = NULL;
	t_env	*env;
	t_env	*sorted_env;
	t_env	*iter;

	env = duplicate_env_list(minishell->env_vars);
	sorted_env = insertion_sort(env);
	iter = sorted_env;
	while (iter)
	{
		if (current_cmd->is_pipe)
			output = join_all(iter);
		else
			printf("declare -x %s=\'%s\'\n", iter->name, iter->value);
		iter = iter->next;
	}
	if (output)
		minishell->output = output;
	free_env_list(sorted_env);
}
