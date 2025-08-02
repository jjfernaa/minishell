-------------
	LEXER
-------------

1. Revisar función handle_quotes() -> si no hay comillas de cierre, imprimo un error únicamente,
pero debemos gestionarlo de otra forma, imprimiendo el error y limpiando todo.

2. Necesitamos el archivo lexer_conversion.c ?

-----------
	ENV
-----------

1. Crear función para crear un char** env que luego pasaremos a execve. Creo que no está implementado.

---------------
	EXECUTOR
---------------

1. Crear char **env desde t_env justo antes de execve. Esta función sólo toma como parámetro un char**

---------------
	BUILTINS
---------------

1. El builtin env debe utilizar t_env, no el char** que es copia de envp y no actualizamos.
2. Cuando ejecutamos echo $? no muestra el exit.status, muestra tal cual $? -> esto es parte de la expansión de variables, comprobar cuando se implemente.


---------------
	GENERAL
---------------

1. Tenemos dos funciones free_array(). Una en parser_utils.c y otra en string_utils.char
	Nos debemos quedar sólo con una, la que tenemos en parser_utils. **HECHO**
2. Eliminar de minishell.h split_input()
3. Eliminar de t_shell char	**envp
4. Eliminar free(input) del main e incorporar input a la estructura t_shell, así centralizamos la limpieza de la memoria.