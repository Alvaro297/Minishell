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

bool	is_in_sd_quotes(t_cmd *cmds)
{
	t_cmd	*current_cmd;
	int		i;
	bool	inside_quotes;

	current_cmd = cmds;
	inside_quotes = false;
	while (current_cmd != NULL)
	{
		if (current_cmd->is_heredoc && current_cmd->here_doc_delim)
		{
			i = 0;
			while (current_cmd->here_doc_delim[i])
			{
				if (current_cmd->here_doc_delim[i][0] == '\''
						&& current_cmd->here_doc_delim[i][ft_strlen(current_cmd->here_doc_delim[i]) - 1] == '\'')
					inside_quotes = true;
				else
					inside_quotes = false;
				i++;
			}
		}
		current_cmd = current_cmd->next;
	}
	return (inside_quotes);
}

static void	fill_minishell_help(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*previous_pwd;

	minishell->output = NULL;
	minishell->howmanycmd = howmanycmds(minishell->cmds);
	previous_pwd = minishell->current_dir;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		minishell->current_dir = ft_strdup(cwd);
	else
	{
		perror("minishell: warning: getcwd failed (directory might have been removed)");
		if (previous_pwd)
			minishell->current_dir = ft_strdup(previous_pwd);
		else
			minishell->current_dir = ft_strdup("");
	}
	if (previous_pwd)
		free(previous_pwd);
}

void	printf_cmd(t_cmd *cmds)
{
    t_cmd	*current_cmd;
    int		i;

    current_cmd = cmds;
    while (current_cmd != NULL)
    {
        printf("--------\n");
        printf("Command: %s\n", current_cmd->cmd ? current_cmd->cmd : "(null)");

        // Argumentos
        if (current_cmd->args)
        {
            for (i = 0; current_cmd->args[i]; i++)
                printf("Arg[%d]: %s\n", i, current_cmd->args[i]);
        }

        // Redirecciones de entrada y salida
        if (current_cmd->infile)
            printf("Infile: %s\n", current_cmd->infile);
        if (current_cmd->outfile)
            printf("Outfile: %s\n", current_cmd->outfile);

        // Heredocs
        if (current_cmd->is_heredoc && current_cmd->here_doc_delim)
        {
            for (i = 0; current_cmd->here_doc_delim[i]; i++)
                printf("Heredoc delim[%d]: %s\n", i, current_cmd->here_doc_delim[i]);
        }

        // Outfiles múltiples (si tienes soporte)
        if (current_cmd->outfile_array)
        {
            for (i = 0; current_cmd->outfile_array[i]; i++)
                printf("Outfile_array[%d]: %s\n", i, current_cmd->outfile_array[i]);
        }

        // Pipe
        printf("Is pipe: %s\n", current_cmd->is_pipe ? "yes" : "no");

        // Siguiente comando
        current_cmd = current_cmd->next;
    }
    printf("--------\n");
}

void	fill_minishell(char *input, t_minishell *minishell, char **envp)
{
	if (minishell->env_vars == NULL)
		minishell->env_vars = init_env(envp);
	else if (minishell->env_vars == NULL && !envp)
		minishell->env_vars = init_env_without_env();
	minishell->input = ft_quote_printf(minishell, input, true);
	if (input && *input)
	{
		set_special_var(minishell);
		add_history(input);
		add_to_history(minishell, input);
	}
	if (minishell->input == NULL)
	{
		if (minishell->cmds)
		{
			free_cmd_list(minishell->cmds);
			minishell->cmds = NULL;
		}
		free(input);
		return ;
	}
	minishell->cmds = parsing_input(minishell, input);
	if (minishell->cmds == NULL)
		return (free(input));

	printf_cmd(minishell->cmds);
	fill_minishell_help(minishell);
}
