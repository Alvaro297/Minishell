/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 04:04:20 by paperez-          #+#    #+#             */
/*   Updated: 2025/02/12 11:54:57 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

void	exitaux(void)
{
	ft_putstr("./pipex infile cmd cmd outfile\n");
	exit(0);
}

int	open_f(char *file, int sw, t_cmd *cmd)
{
	int	r;

	if (sw == 0)
		r = open(file, O_RDONLY, 0777);
	if (sw == 1 && cmd->outfile_modes == 1)
		r = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (sw == 1 && cmd->outfile_modes == 2)
		r = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	return (r);
}

void	freeall(char **m)
{
	int	c;

	c = 0;
	while (m[c])
	{
		free (m[c]);
		c++;
	}
	free (m);
}

char	*getpathaux(char *path, char **env)
{
	char	*key;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		if (ft_strcmp(key, path) == 0)
		{
			free (key);
			return (env[i] + j + 1);
		}
		free (key);
		i++;
	}
	return (NULL);
}

char	*getpath(char *cmd, char **env)
{
	char	**paths;
	char	*eachpath;
	char	*fullpath;
	int		i;

	paths = ft_split(getpathaux("PATH", env), ':');
	i = 0;
	while (paths[i])
	{
		eachpath = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(eachpath, cmd);
		free (eachpath);
		if (access(fullpath, F_OK | X_OK) == 0)
		{
			freeall(paths);
			return (fullpath);
		}
		free(fullpath);
		i++;
	}
	freeall(paths);
	return (cmd);
}
