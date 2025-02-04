# include "../minishell.h"

void	parse_input_help(t_cmd **new_cmd, char *command, int position, char **array_command)
{
	t_cmd	*tmp;
	char	**command_splited;
	int		i;

	i = 0;
	tmp = *new_cmd;
	command_splited = ft_split_modified(command, ' '); //Funcion a diseñar por ti Max tiene que hacer lo que te he dicho en el audio. 
													   // Dividir por espacios o lo que sea excepto si está entre comillas simples o compuestas
	tmp->cmd = command_splited[0];
	while (condition)
	{
		/* code */
	}
	
}