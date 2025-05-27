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
	char *oldpwd;

	oldpwd = getenv("PWD");
	if (oldpwd != NULL)
		set_env(&minishell->env_vars, "OLDPWD", oldpwd);
	else
		set_env(&minishell->env_vars, "OLDPWD", "");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		set_env(&minishell->env_vars, "PWD", path);
	else
		set_env(&minishell->env_vars, "PWD", cwd);
}

static char	*cd_path(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*path;
	char	*env_home;

	if ((current_cmd->args[1] &&
		(((current_cmd->args[1][0] == '~' && current_cmd->args[1][1] == '\0')
			|| (current_cmd->args[1][0] == '-' && current_cmd->args[1][1] == '-' 
				&& current_cmd->args[1][2] == '\0'))))
		|| !current_cmd->args[1])
	{
		env_home = get_env_value(minishell->env_vars, "HOME", false);
		if (env_home)
			path = ft_strdup(env_home);
		else
			path = NULL;
	}
	else
	{
		if (current_cmd->args[1])
			path = ft_strdup(current_cmd->args[1]);
		else
			path = NULL;
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

	if (current_cmd->args[1] && current_cmd->args[2])
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
		free(path);
		return (1);
	}
	handle_cd_help(minishell, path, cwd);
	free(path);
	return (0);
}
