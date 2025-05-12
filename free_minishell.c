# include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp;
	int i;
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		if (cmd->args)
		{
			for (i = 0; cmd->args[i]; i++)
				free(cmd->args[i]);
			free(cmd->args);
		}
		if (cmd->outfile_array)
		{
			for (i = 0; cmd->outfile_array[i]; i++)
				free(cmd->outfile_array[i]);
			free(cmd->outfile_array);
		}
		if (cmd->here_doc_delim)
		{
			for (i = 0; cmd->here_doc_delim[i]; i++)
				free(cmd->here_doc_delim[i]);
			free(cmd->here_doc_delim);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}

void	free_all(t_minishell *minishell)
{
	free_double_array((void **)minishell->history);
	free(minishell->current_dir);
	free(minishell->input);
	free(minishell->output);
	free_cmd_list(minishell->cmds);
	free_env_list(minishell->env_vars);
}