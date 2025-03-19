# include "../minishell.h"

/*int	error_control(t_minishell minishell)
{
//TODO discutir con Alvaro los codigos de error para cada comando(esta funcion sería para diferenciar entre distintos errores, pero igual no es necesario y podemos poner como código de error -1 sea cual sea el error del input)
//Para los comandos que se ejecutan con execve podríamos conservar el código de error que nos da execve(creo que siempre es -1 pero no estoy seguro, y para los builtins tenemos que decidir nosotros que código de error ponemos.)
}**/

void	ft_error(t_minishell *minishell)
{
	int	c;

	c = 0;
	while (minishell->cmds->args[c])
	{
		free(minishell->cmds->args[c]);
		c++;
	}
	free(minishell->cmds->args);
	free(minishell->cmds->infile);
	free(minishell->cmds->outfile);
	free(minishell->cmds->cmd);
	free(minishell->cmds->args);
	free(minishell->input);
	free(minishell->pids);
	free(minishell->output);
	//minishell.last_exit_status = -1;
	printf("error");
}
/*
int	error_management(t_minishell *minishell)
{
	int c;

	c = 0;
	if (minishell->input == NULL || minishell->input == 0)
		return (1);
	if (!check_syntax(minishell))
		return (1);
	if (handle_redirection(minishell) != 0)
		return (1);
	return (0);
}*/
