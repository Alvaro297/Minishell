#include "../minishell.h"

int	handle_infile(char *infile)
{
	int	fd;
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			fprintf(stderr, "Error: El archivo '%s' no existe para redirección de entrada.\n", infile);
		else if (errno == EACCES)
			fprintf(stderr, "Error: Permisos insuficientes para leer el archivo '%s'.\n", infile);
		else
			perror("Error al abrir el archivo de entrada");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error al redirigir la entrada estándar");
		close(fd);
		return (-1);
	}
}

int	handle_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			fprintf(stderr, "Error: Permisos insuficientes para escribir en el archivo '%s'.\n", outfile);
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

