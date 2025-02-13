Funciones a implementar

*free_double_array(parsed_input);* // En parsing_cmd
Funcion para liberar un array de doble puntero. Sin importar su tamaño. Se utilizara en varias funciones.

command_splited = ft_split_modified(command, ' '); // En parsing_cmd
Funcion para splitear un string por lo que le pases por parametro en el segundo lugar (En el ejemplo un espacio). Tiene que splitear en este caso por espacio todo excepto si el caracter está entre comillas. Ya sean dobles o simples '' "".

Tengo algo parecido en la función ft_quote_printf del fichero expand_variable.c

Porque se necesita command_splited.

A la hora de crear un t_cmd va a recibir lo siguiente de : echo "'Hello | world" | grep  foo > output.txt (input de minishell)
Lo dividirá a: echo 'Hello | world, | y a grep  foo > output.txt
Parsing_cmd recogera por partes primero echo 'Hello | world y luego grep  foo > output.txt porque salta de 2 en 2
Una vez que tengas echo 'Hello | world' Lo quiero dividir en (echo) ('Hello | world'). Si tuviera mas espacios pues mas

## Señales

He implementado las señales. Pero es importante que entiendas que falta algo para las señales. A la hora de hacer la ejecucion necesitamos poner la señal de SIGINT (Ctr + C) en los procesos hijos SOLO en los hijos para que si en mitad del proceso lo quieren parar este finalize. Ej:

 if (pid == 0) // Proceso hijo
	{
		signal(SIGINT, SIG_DFL); // Restaurar SIGINT en el hijo
		char *args[] = {cmd, NULL};
		execvp(args[0], args);
		perror("execvp"); // Solo se ejecuta si execve falla
		exit(1);
	}
	else if (pid > 0) // Proceso padre
	{
		int status;
		waitpid(pid, &status, 0);
	}
