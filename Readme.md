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

Entiendo, quieres asegurarte de que todas las posibles comprobaciones de errores se manejen adecuadamente en tu [`minishell`](minishell ). Aquí hay una lista de comprobaciones de errores que deberías considerar implementar en tu función error_control y en otras partes de tu código:

### Comprobaciones de errores en error_control

1. **Verificar la existencia de variables de entorno críticas**:
   - `PWD`: Verifica si la variable de entorno `PWD` está presente y es válida.
   - `HOME`: Verifica si la variable de entorno `HOME` está presente y es válida.
   - `PATH`: Verifica si la variable de entorno `PATH` está presente y es válida.

2. **Verificar la validez de los valores de las variables de entorno**:
   - Asegúrate de que los valores de las variables de entorno no sean `NULL` o cadenas vacías.

3. **Verificar la existencia de archivos y directorios**:
   - Para comandos que requieren archivos o directorios específicos (por ejemplo, `cd`, `pwd`), verifica si los archivos o directorios existen y son accesibles.

4. **Verificar permisos de archivos y directorios**:
   - Asegúrate de que el usuario tenga los permisos necesarios para acceder o modificar archivos y directorios.

5. **Verificar la validez de los comandos**:
   - Asegúrate de que los comandos ingresados sean válidos y estén disponibles en el sistema.
   - Verifica si el comando es un comando interno o externo.

6. **Verificar la sintaxis de los comandos**:
   - Asegúrate de que la sintaxis de los comandos sea correcta (por ejemplo, no permitir pipes (`|`) al inicio o final de la línea de comandos).

7. **Manejo de errores de redirección**:
   - Verifica si las redirecciones de entrada (`<`) y salida (`>`, `>>`) son válidas y si los archivos especificados existen y son accesibles.

8. **Verificar la validez de los argumentos**:
   - Asegúrate de que los argumentos de los comandos sean válidos y no contengan caracteres no permitidos.

### Ejemplo de error_control

Aquí hay un ejemplo de cómo podrías implementar algunas de estas comprobaciones en la función error_control:

```c
#include "minishell.h"

int	error_control(t_minishell *minishell)
{
	// Verificar si la variable de entorno PWD está presente
	if (get_env_value(minishell->env_vars, "PWD") == NULL)
	{
		ft_putstr_fd("minishell: pwd: PWD not set\n", 2);
		return (1); // Retornar 1 en caso de error
	}

	// Verificar si la variable de entorno HOME está presente
	if (get_env_value(minishell->env_vars, "HOME") == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1); // Retornar 1 en caso de error
	}

	// Verificar si la variable de entorno PATH está presente
	if (get_env_value(minishell->env_vars, "PATH") == NULL)
	{
		ft_putstr_fd("minishell: command not found: PATH not set\n", 2);
		return (1); // Retornar 1 en caso de error
	}

	// Otras verificaciones de error...

	return (0); // Retornar 0 si no hay errores
}
```

### Comprobaciones de errores en otras partes del código

1. **Verificar la asignación de memoria**:
   - Asegúrate de que todas las asignaciones de memoria (`malloc`, `calloc`, `realloc`) se verifiquen para evitar errores de memoria.

2. **Verificar la apertura de archivos**:
   - Asegúrate de que todas las aperturas de archivos (`fopen`, `open`) se verifiquen para evitar errores de archivo.

3. **Verificar la ejecución de comandos externos**:
   - Asegúrate de que la ejecución de comandos externos (`execve`, `system`) se verifique para evitar errores de ejecución.

4. **Manejo de señales**:
   - Asegúrate de que las señales (`SIGINT`, `SIGQUIT`) se manejen adecuadamente para evitar que el programa se cierre inesperadamente.

### Resumen

- **Verificar la existencia de variables de entorno críticas**: `PWD`, `HOME`, `PATH`.
- **Verificar la validez de los valores de las variables de entorno**.
- **Verificar la existencia de archivos y directorios**.
- **Verificar permisos de archivos y directorios**.
- **Verificar la validez de los comandos**.
- **Verificar la sintaxis de los comandos**.
- **Manejo de errores de redirección**.
- **Verificar la validez de los argumentos**.
- **Verificar la asignación de memoria**.
- **Verificar la apertura de archivos**.
- **Verificar la ejecución de comandos externos**.
- **Manejo de señales**.

Con estas comprobaciones, podrás manejar adecuadamente los errores en tu [`minishell`](minishell ) y asegurarte de que el programa sea robusto y confiable.

Entiendo, quieres asegurarte de que todas las posibles comprobaciones de errores se manejen adecuadamente en tu [`minishell`](minishell ). Aquí hay una lista de comprobaciones de errores que deberías considerar implementar en tu función error_control y en otras partes de tu código:

### Comprobaciones de errores en error_control

1. **Verificar la existencia de variables de entorno críticas**:
   - `PWD`: Verifica si la variable de entorno `PWD` está presente y es válida.
   - `HOME`: Verifica si la variable de entorno `HOME` está presente y es válida.
   - `PATH`: Verifica si la variable de entorno `PATH` está presente y es válida.

2. **Verificar la validez de los valores de las variables de entorno**:
   - Asegúrate de que los valores de las variables de entorno no sean `NULL` o cadenas vacías.

3. **Verificar la existencia de archivos y directorios**:
   - Para comandos que requieren archivos o directorios específicos (por ejemplo, `cd`, `pwd`), verifica si los archivos o directorios existen y son accesibles.

4. **Verificar permisos de archivos y directorios**:
   - Asegúrate de que el usuario tenga los permisos necesarios para acceder o modificar archivos y directorios.

5. **Verificar la validez de los comandos**:
   - Asegúrate de que los comandos ingresados sean válidos y estén disponibles en el sistema.
   - Verifica si el comando es un comando interno o externo.

6. **Verificar la sintaxis de los comandos**:
   - Asegúrate de que la sintaxis de los comandos sea correcta (por ejemplo, no permitir pipes (`|`) al inicio o final de la línea de comandos).

7. **Manejo de errores de redirección**:
   - Verifica si las redirecciones de entrada (`<`) y salida (`>`, `>>`) son válidas y si los archivos especificados existen y son accesibles.

8. **Verificar la validez de los argumentos**:
   - Asegúrate de que los argumentos de los comandos sean válidos y no contengan caracteres no permitidos.

### Comprobaciones de errores en otras partes del código

1. **Verificar la asignación de memoria**:
   - Asegúrate de que todas las asignaciones de memoria (`malloc`, `calloc`, `realloc`) se verifiquen para evitar errores de memoria.

2. **Verificar la apertura de archivos**:
   - Asegúrate de que todas las aperturas de archivos (`fopen`, `open`) se verifiquen para evitar errores de archivo.

3. **Verificar la ejecución de comandos externos**:
   - Asegúrate de que la ejecución de comandos externos (`execve`, `system`) se verifique para evitar errores de ejecución.

4. **Manejo de señales**:
   - Asegúrate de que las señales (`SIGINT`, `SIGQUIT`) se manejen adecuadamente para evitar que el programa se cierre inesperadamente.

### Resumen

- **Verificar la existencia de variables de entorno críticas**: `PWD`, `HOME`, `PATH`.
- **Verificar la validez de los valores de las variables de entorno**.
- **Verificar la existencia de archivos y directorios**.
- **Verificar permisos de archivos y directorios**.
- **Verificar la validez de los comandos**.
- **Verificar la sintaxis de los comandos**.
- **Manejo de errores de redirección**.
- **Verificar la validez de los argumentos**.
- **Verificar la asignación de memoria**.
- **Verificar la apertura de archivos**.
- **Verificar la ejecución de comandos externos**.
- **Manejo de señales**.
