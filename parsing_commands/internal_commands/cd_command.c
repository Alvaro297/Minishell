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

#include "../../minishell.h"

static void	handle_cd_help(t_minishell *minishell, char *path, char *cwd)
{
	char	*oldpwd;
	char	*new_pwd;

	new_pwd = NULL;
	oldpwd = getenv("PWD");
	if (oldpwd != NULL)
		set_env(&minishell->env_vars, "OLDPWD", oldpwd);
	else
		set_env(&minishell->env_vars, "OLDPWD", "");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		oldpwd = get_env_value(minishell->env_vars, "PWD", false);
		if (oldpwd && oldpwd[0] && ft_strncmp(path, "..", 2) == 0
			&& ft_strlen(path) == 2)
		{
			new_pwd = ft_strjoin(oldpwd, "/..");
			set_env(&minishell->env_vars, "PWD", new_pwd);
			free(new_pwd);
		}
		else
			set_env(&minishell->env_vars, "PWD", "..");
	}
	else
		set_env(&minishell->env_vars, "PWD", cwd);
}

static bool	is_home_cd_arg(t_cmd *current_cmd)
{
	if (!current_cmd->args[1])
		return (true);
	if ((current_cmd->args[1][0] == '~' && current_cmd->args[1][1] == '\0')
		|| (current_cmd->args[1][0] == '-' && current_cmd->args[1][1] == '-' && current_cmd->args[1][2] == '\0'))
		return (true);
	return (false);
}

static char	*cd_path(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*path;
	char	*env_home;
	char	*env_oldpwd;

	path = NULL;
	if (is_home_cd_arg(current_cmd))
	{
		env_home = get_env_value(minishell->env_vars, "HOME", false);
		if (env_home)
			path = ft_strdup(env_home);
	}
	else if (current_cmd->args[1]
		&& current_cmd->args[1][0] == '-'
		&& current_cmd->args[1][1] == '\0')
	{
		env_oldpwd = get_env_value(minishell->env_vars, "OLDPWD", false);
		if (env_oldpwd)
			path = ft_strdup(env_oldpwd);
	}
	else if (current_cmd->args[1])
		path = ft_strdup(current_cmd->args[1]);
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

int	handle_cd(t_cmd *current_cmd, t_minishell *minishell)
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
