-------------
	LEXER
-------------

1. Revisar función handle_quotes() -> si no hay comillas de cierre, imprimo un error únicamente,
pero debemos gestionarlo de otra forma, imprimiendo el error y limpiando todo.

2. Necesitamos el archivo lexer_conversion.c ?

-----------
	ENV
-----------

---------------
	EXECUTOR
---------------

1. Crear char **env desde t_env justo antes de execve. Esta función sólo toma como parámetro un char**
2. No funciona las redirecciones con archivos de entradas y salidas.

---------------
	BUILTINS
---------------

1. El builtin env debe utilizar t_env, no el char** que es copia de envp y no actualizamos. **HECHO**
2. buitltin env -> manejar error cuando le pasamos un argumento ej. env hola
Salida bash ->
dponce@PC-dponce:~$ env hola
env: ‘hola’: No such file or directory

---------------
	GENERAL
---------------

3. Eliminar de t_shell char	**envp
4. Eliminar free(input) del main e incorporar input a la estructura t_shell, así centralizamos la limpieza de la memoria.