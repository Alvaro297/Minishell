##Que pasa cuando pones outfiles entre medias de los comandos.

echo "hola" | grep "ho" > salida.txt | sort
❌ ¿Qué pasa?

El > en grep redirige la salida de grep a salida.txt.
El pipe | de después de grep no pasa nada, porque ya se ha redirigido la salida al archivo y no queda nada para pasar al siguiente comando (sort).
sort no recibe nada del pipe.

Hey pablo. he estado investigando y resulta que si pones varios outfiles pero fuera de las pipes los trata de una manera extraña. Ejemplo:

echo "hola" | grep "ho" > salida.txt | wc -l > salida2.txt
En este caso echo y grep se harian y se meten en la salida.txt y a wc -l no recibe nada. Y en salida2.txt lo crea y escribe 0 (En el caso de wc -l) Pero como output no recibe nada. Ya he modificado eso pero es mas en ejecución para que lo tengas en cuenta.