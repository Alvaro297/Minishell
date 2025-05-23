##Que pasa cuando pones outfiles entre medias de los comandos.

echo "hola" | grep "ho" > salida.txt | sort
❌ ¿Qué pasa?

El > en grep redirige la salida de grep a salida.txt.
El pipe | de después de grep no pasa nada, porque ya se ha redirigido la salida al archivo y no queda nada para pasar al siguiente comando (sort).
sort no recibe nada del pipe.

Hey pablo. he estado investigando y resulta que si pones varios outfiles pero fuera de las pipes los trata de una manera extraña. Ejemplo:

echo "hola" | grep "ho" > salida.txt | wc -l > salida2.txt
En este caso echo y grep se harian y se meten en la salida.txt y a wc -l no recibe nada. Y en salida2.txt lo crea y escribe 0 (En el caso de wc -l) Pero como output no recibe nada. Ya he modificado eso pero es mas en ejecución para que lo tengas en cuenta.

## 13/03/2025

Como te he comentado en whatsapp para mirar los codigos de error la que debemos de utilizar es waitpid esta funciona con casi todos excepto 4. (Habria que preguntar alli)

Tambien si cortamos un proceso con ctrl+c el codigo de error es 130. Pero ese waitpid lo coje.

He añadido la funcion free_double_array en una carpeta llamada free_minishell que ahi es donde vamos a eliminar todo despues.
Free_double_array elimina cualquier tipo de array doble no solo los de char. Eso si antes de llamarla casteala a (void **) a lo que quieras eliminar.
Ej:
free_double_array((void **)parsed_input);


## 20/03/2025

Holi que tal. He hecho la funcion de howmanycmds por tí al ver que era una tonteria. No tienes que comprobar si los pipes estan entre comillas solo contar cuantas listas encadenadas hay.
Haz pull.

He estado mirando el codigo y creo que debemos dividirlo en 1er comando los del medio y ultimo. 
1er comando que comprobaremos si este es un builtin para crear hijos o no. Los del medio que comprobaremos si es builtin o no pero crearemos el hijo independientemente y el del final para la redireccion del outfile. Ahora mismo creo que lo tenemos como un pipex basico.

## 23/03/2025

Hola qui pasa tenes segarro? Pues bueno he estado mirando y ya he solucionado el error estaba en append_cmds en el parsing_cmd tienes que corregir export te lo dejo a ti y asi miras la funcion de los builtin mas compleja. He corregido cd y funciona perfectamente al igual que echo.
El problema en export son 3:
declare -x _="./Minishell"
declare -x roo="prueba"
	No se puede hacer export y crear una variable en el primer comando. Da doble freeze pero mira a ver si es porque es NULL el tipo minishell->env_vars
	Se crea la variable _="./Minishell" (Creo que lo coge de la ejecucion). Esto sin ponerle nada
	Las variables que se crean les falta la ultima letra (Seguramente sea un simple +1 pero investiga)

## 23\03\2025

P:El programa tiene que entrar el pipex siempre porque si hay redireccion internal_commands no lo 
gestiona. Por tanto hay que hacerlo dentro de pipex aunnque no haya que crear ningun proceso hijo.
Tengo que arreglar pipex entero creando la estructura desde cero porque siino me voy a volver loco.
Primero gestionar los pipes creando bien los porcesos hijos y despues ya gestiona las redirecciones que será más sencillo.

## 24/03/2025

No estoy seguro de si tengo que usar nuestras env_vars en pipex o puedo usar envp. Aunque pase env_vars a char** execve sigue dando problemas, y no consigo que funcione igual con env_vars que con envp. De momento lo dejo con envp, hasta implementar el pipex, y despues sii es necesario (que creo que si, ya que podemos usar variables que hayamos definido a posteriori) hago los cambios necesarios para que funcione con nuestras variables de entorno, que no creo que sea dificil.
Por otra parte el problema de open: Permission denied me esta volviendoo loco, no entiendo que carajo puede estar pasando ya que aunque no haya redirecciones ni archivos en el comando sigue dando ese error, no hay forma de quitarselo.

## 23/05/2025

Hola Pablete el error lo he localizado pero hay un problema con los putos heredocs
cat << hola | cat << |
-bash: syntax error near unexpected token `|'
> hola
Si te fijas aqui se mete al here_doc de manera correcta pero anteriormente hay un problema y lo muestra.
Asi que hay que hacer los here_docs anteriores pero al final no va a hacer nada de nada da igual si hay redirecciones o lo que sea. Es exactamente lo mismo que lanzar un comando vacio (el resultado).
Yo el mensaje de error en mi codigo ya lo muestro sin que de ningun fallo (Luego lo modificare en el tuyo) Pero el comando se lanza como si no hubiese ningun here_doc y hay que ver como evitar eso.
Igual hay que preguntar el tema del here_doc el error ese porque creo que lanzamos el mensaje de error y ya. Nos quitamos de problemas
Hay que hacer $_ que es el ultimo argumento del comando (Es facil y me encargo yo)
## Queda:
	Here_docs: Pablete (Casi)
	$?: Pablete
	Errores: Ambos
		Yo (Martín): sacare en el parseo los mensajes de error tipo el del here_doc.
		Tu (Pablete): el codigo de error y errores de comandos mal escritos. | |
	Normi: Ambos