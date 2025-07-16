🧩 Punto 4: Redirección sin comando

📌 Ejemplo:
< archivo.txt

🧠 ¿Qué hace Bash aquí?
Bash no lanza un error. Lo interpreta como:

“Ejecuta un comando vacío que toma su entrada de archivo.txt”.

Pero como no hay comando, el shell simplemente abre el archivo y no hace nada.

🔍 Bash ejecuta esto silenciosamente y retorna 0 si el archivo existe.

📋 ¿Qué pasa si el archivo no existe?
< noexiste.txt
➡️ Bash lanza:

bash: noexiste.txt: No such file or directory
Y retorna código 1.

✅ ¿Qué deberías hacer tú en minishell?
Tienes dos opciones válidas:

❌ Rechazarlo como error de sintaxis	Si no hay T_WORD antes o después de una redirección → error	Evitas procesar cosas “vacías”	No compatible con Bash
✅ Aceptarlo	No haces parsing a ningún t_cmd, pero procesas las redirecciones y herencias	Comportamiento idéntico a Bash	Complica ligeramente el executor

👉 Mi recomendación para un parser básico: puedes permitirlo, pero asegúrate de que tu executor no intente ejecutar un comando vacío.

🧩 Punto 6: Redirecciones sin comando intermedio

📌 Ejemplo:
> out.txt < in.txt
🧠 ¿Qué hace Bash aquí?
Bash también lo permite. Interpreta:

“Ejecuta un comando vacío, con salida en out.txt y entrada desde in.txt”.

De nuevo:
Si ambos archivos existen, no imprime error.
Si alguno no existe o no tiene permisos, lanza error.

🔍 No ejecuta nada, pero sí procesa las redirecciones.

✅ ¿Qué pasa si lo haces en minishell?
En tu parser, podrías acabar con una lista t_cmd con un único nodo:

argv == NULL
infile = "in.txt"
outfile = "out.txt"

👉 Luego tu executor deberá detectar que argv es NULL y simplemente abrir/cerrar los archivos sin fork ni execve.

✅ Conclusión para tu minishell
Caso							Bash lo permite	Recomendación minishell
< archivo.txt sin comando		✅ Sí			✅ Puedes permitirlo
> out.txt < in.txt sin comando	✅ Sí			✅ Puedes permitirlo
cat > sin archivo de salida		❌ No			❌ Debe dar error

🛠 Recomendación práctica
Parser: permite redirecciones sin comandos si están bien formadas (redir → T_WORD).

Executor: si argv == NULL, no intentes ejecutar, pero sí maneja redirecciones si existen.

Mensaje claro si el archivo falla al abrirse (perror() en el executor).