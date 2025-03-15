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
	free(path);
	set_env(&minishell->env_vars, "OLDPWD", getenv("PWD"));
	cwd = getcwd(NULL, 0);
	set_env(&minishell->env_vars, "PWD", cwd);
	free(cwd);
}

static char	*cd_path(t_minishell *minishell)
{
	char	*path;

	if (minishell->cmds->args[1] &&
		minishell->cmds->args[1][0] == '~' && minishell->cmds->args[1][1] == '\0')
		path = get_env_value(minishell->env_vars, "HOME");
	else
		path = minishell->cmds->args[1] ? ft_strdup(minishell->cmds->args[1]) :
			get_env_value(minishell->env_vars, "HOME");
	return (path);
}

int		handle_cd(t_minishell *minishell)
{
	char	*path;
	char	*cwd;

	if (minishell->cmds->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	path = cd_path(minishell);
	if (!path)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free(path);
		return (1);
	}
	handle_cd_help(minishell, path, cwd);
	return (0);
}
