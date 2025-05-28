/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_archives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 20:36:27 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 20:36:27 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_infile_error(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("Error: El archivo '", 2);
			ft_putstr_fd(infile, 2);
			ft_putstr_fd("' no existe para redirección de entrada.\n", 2);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd("Error: Permisos insuficientes ", 2);
			ft_putstr_fd("para leer el archivo '", 2);
			ft_putstr_fd(infile, 2);
			ft_putstr_fd("'.\n", 2);
		}
		else
			perror("Error al abrir el archivo de entrada");
		return (-1);
	}
	return (fd);
}

int	handle_infile(char *infile)
{
	int	fd;

	fd = handle_infile_error(infile);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error al redirigir la entrada estándar");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("Error: Permisos insuficientes ", 2);
			ft_putstr_fd("para escribir en el archivo '", 2);
			ft_putstr_fd(outfile, 2);
			ft_putstr_fd("'.\n", 2);
		}
		else
			perror("Error al abrir el archivo de salida");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error al redirigir la salida estándar");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirection(t_cmd *cmd)
{
	if (handle_infile(cmd->infile) != 0)
		return (1);
	if (handle_outfile(cmd->infile) != 0)
		return (1);
	return (0);
}
