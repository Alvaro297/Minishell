# include "../minishell.h"

/* El comando como norma general estara en 1era posicion pero hay veces que no es asi. Puede haber antes una redireccion.
   Es decir: < input (comando) hay que tratar esos casos. Tambien puede pasar este caso < input > output (comando)*/
char *find_command(char **command_splited)
{
	int		i;

	i = 0;
	while (command_splited[i])
	{
		if ((ft_strncmp(command_splited[i], "<", 1) == 0 ||
			ft_strncmp(command_splited[i], ">", 1) == 0 ||
			ft_strncmp(command_splited[i], ">>", 2) == 0) &&
			ft_strlen(command_splited[i]) <= 2)
		{
			i++;
			if ((ft_strncmp(command_splited[i], "<", 1) == 0 ||
				ft_strncmp(command_splited[i], ">", 1) == 0 ||
				ft_strncmp(command_splited[i], ">>", 2) == 0) &&
				ft_strlen(command_splited[i]) <= 2)
				return (NULL);
			i++;
		}
		else
		{
			return (command_splited[i]);
		}
	}
	return (NULL);
}
