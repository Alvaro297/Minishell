/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:32:03 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:32:03 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

static void	handle_cd_help(t_minishell *minishell, char *path, char *cwd)
{
	printf("handle_cd_help: path = %s\n", path);
	free(path);
	set_env(&minishell->env_vars, "OLDPWD", getenv("PWD"));
	getcwd(cwd, sizeof(cwd));
	printf("handle_cd_help: new cwd = %s\n", cwd);
	set_env(&minishell->env_vars, "PWD", cwd);
}

static char	*cd_path(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*path;

	if ((current_cmd->args[1] &&
		(((current_cmd->args[1][0] == '~' && current_cmd->args[1][1] == '\0')
			|| (current_cmd->args[1][0] == '-' && current_cmd->args[1][1] == '-' && current_cmd->args[1][2] == '\0'))))
		|| !current_cmd->args[1])
	{
		path = get_env_value(minishell->env_vars, "HOME");
		printf("cd_path: HOME path = %s\n", path);
	}
	else
	{
		path = current_cmd->args[1] ? ft_strdup(current_cmd->args[1]) :
			get_env_value(minishell->env_vars, "HOME");
		printf("cd_path: specified path = %s\n", path);
	}
	return (path);
}

static int	error_cd(char *path)
{
	if (!path)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (access(path, R_OK | X_OK) != 0)
	{
		perror("minishell: cd");
		free(path);
		return (1);
	}
	return (0);
}

int		handle_cd(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*path;
	char	cwd[1024];

	printf("handle_cd: current_cmd->args[1] = %s\n", current_cmd->args[1]);
	if (current_cmd->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	path = cd_path(current_cmd, minishell);
	if (error_cd(path) == 1)
		return (1);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	handle_cd_help(minishell, path, cwd);
	return (0);
}
