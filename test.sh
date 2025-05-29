export VAR1="hola"
export VAR2='mundo'
echo "$VAR1 $VAR2"
echo 'El valor de HOME es:' "$HOME"
echo "comillas 'simples' y \"dobles\""
echo "" | cat
echo $VAR1 | grep h
echo $VAR2 | grep o
echo "fin de test"
exit