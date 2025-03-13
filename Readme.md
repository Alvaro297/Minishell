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