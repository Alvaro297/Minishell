# include "../minishell.h"

int count_strings(char **array)
{
	int	count;
	count = 1;
	while (array[count] != NULL)
	{
		count++;
	}
	return (count);
}

void	parse_input_help(t_cmd **new_cmd, char *command, int position, char **array_command)
{
	t_cmd	*tmp;
	char	**command_splited;
	int		i;

	i = 1;
	tmp = *new_cmd;
	command_splited = ft_split_modified(command, ' '); //Funcion a diseñar por ti Max tiene que hacer lo que te he dicho en el audio. 
													   // Dividir por espacios o lo que sea excepto si está entre comillas simples o compuestas
	tmp->cmd = ft_strdup(command_splited[0])
	tmp->args = malloc((count_strings(command_splited) + 1) * sizeof(char *));
	while (command_splited[i])
	{
		tmp->args[i] = ft_strdup(command_splited[i]);
		i++;
	}
	tmp->args[i] = NULL;
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->append = 0;
	tmp->is_pipe = false;
	tmp->is_background = false;
	tmp->next = NULL;
	i = 0;
	while (command_splited[i])
		free(command_splited[i++]);
	free(command_splited);
}
