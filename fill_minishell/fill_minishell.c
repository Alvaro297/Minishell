/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 20:03:50 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-24 20:03:50 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmds(t_cmd *cmds)
{
	int i;
	while (cmds)
	{
		printf("  Comando: %s\n", cmds->cmd ? cmds->cmd : "(null)");
		printf("  Args: ");
		if (cmds->args)
		{
			for (i = 0; cmds->args[i]; i++)
				printf("[%s] ", cmds->args[i]);
		}
		printf("\n");
		printf("  Infile: %s\n", cmds->infile ? cmds->infile : "(null)");
		printf("  Outfile: %s\n", cmds->outfile ? cmds->outfile : "(null)");
		printf("  Outfile_array: ");
		if (cmds->outfile_array)
		{
			for (i = 0; cmds->outfile_array[i]; i++)
				printf("[%s] ", cmds->outfile_array[i]);
		}
		printf("\n");
		printf("  Outfile_modes: %d\n", cmds->outfile_modes);
		printf("  is_pipe: %d\n", cmds->is_pipe);
		printf("  is_heredoc: %d\n", cmds->is_heredoc);
		printf("  Here_doc_delim: ");
		if (cmds->here_doc_delim)
		{
			for (i = 0; cmds->here_doc_delim[i]; i++)
				printf("[%s] ", cmds->here_doc_delim[i]);
		}
		printf("\n");
		printf("-------------------------\n");
		cmds = cmds->next;
	}
}

static void	fill_minishell_help(t_minishell *minishell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (minishell->current_dir)
			free(minishell->current_dir);
		minishell->current_dir = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
}

void	fill_minishell(char *input, t_minishell *minishell, char **envp)
{	
	if (minishell->env_vars == NULL)
		minishell->env_vars = init_env(envp);
	minishell->input = ft_quote_printf(minishell, input);
	if (minishell->input == NULL)
	{
		free(input);
		return ;
	}
	minishell->cmds = parsing_input(minishell, input);
	print_cmds(minishell->cmds);
	minishell->output = NULL;
	minishell->howmanycmd = howmanycmds(minishell->cmds);
	if (input && *input)
	{
		add_history(input);
		add_to_history(minishell, input);
	}
	fill_minishell_help(minishell);
}
