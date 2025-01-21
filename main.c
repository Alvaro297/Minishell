#include "minishell.h"

void	minishell(char **envp)
{
	char	*input;
	
	while (1) 
	{
		input = readline("Minishell: ");
		if (input == NULL || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			break;
		printf("%s\n", input);
		free(input);
	}
	//No hay que poner argumentos en la minishell a la hora de la ejecución.
	//Desde aqui comenzamos
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		printf("Bad arguments in the program");
		return (EXIT_SUCCESS);
	}
	minishell(envp);
	return (EXIT_SUCCESS);
}
