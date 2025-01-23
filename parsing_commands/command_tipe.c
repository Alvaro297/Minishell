#include "minishell.h"

static void	internal_commands(char *input, char **envp)
{
	if (ft_strnstr(input, "exit ", 5))
		/* code */
	else if (ft_strnstr(input, "cd ", 3))
		/* code */
	else if (ft_strnstr(input, "pwd ", 4))
		/* code */
	else if (ft_strnstr(input, "export ", 8))
		/* code */
	else if (ft_strnstr(input, "unset ", 6))
		/* code */
	else if (ft_strnstr(input, "env ", 4))
		/* code */
	else if (ft_strnstr(input, "echo ", 5))
		/* code */
	
}

void	command_tipe(char *input, char **envp)
{
	//Estos son los comandos internos todavia hasy muchos mas tipos de comandos que son:
	//Comandos externos: ls, grep, cat, gcc
	//Redirecciones: < > >> <<
	//Pipes: |
	//Comandos en Segundo plano: &
	//Todo este tipo de comandos irán aquí
	if (ft_strncmp(input, "exit ", 5) == 0 || ft_strncmp(input, "cd ", 3) == 0 ||
		ft_strncmp(input, "pwd ", 4) == 0 || ft_strncmp(input, "export ", 8) == 0 ||
		ft_strncmp(input, "unset ", 6) == 0 || ft_strncmp(input, "env ", 4) == 0 ||
		ft_strncmp(input, "echo ", 5) == 0)
		internal_commands(input, envp);
	
}
