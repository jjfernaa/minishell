ESTRUCTURA Y EXPLICACIÓN DEL PROYECTO MINISHELL

# 🎯 CREACION COPIA DE VARIABLES ENTORNO (📁 env)

📋 Creamos una copia en formato lista enlazada para poder modificar o eliminar las variables con los built-in "export" y "unset", respectivamente.

## 🔧 Pasos a realizar

### ✅ Estructura (📁 env.h)
	Ejemplo ->	key = USER
				value = dponce-g

###	✅ Creación de la copia de las variables entorno 
	✅ Función init_env() -> manejo del flujo
		✅ ♻️ free de todo si falla creación de nuevo nodo (free_env)

	✅ Función new_env_node() -> Creación de un nuevo nodo.
			|-> 🧠 Reserva memoria para el nodo.
			|-> 🧠 Reserva memoria para key.
			|-> 🧠 Reserva memoria para value.
		✅ ♻️ free de key, value y nodo si falla al copiar los valores de key y value

	✅ Función env_add_back() -> Si no es el primer nodo, lo añade al final

	✅ Función free_env() -> ♻️ libera toda la lista enlazada.
			|-> libera key
			|-> libera value
			|-> libera el nodo

### 🚨 Este estructura hay que volver a transformarla a un char** para pasarla como parámetro a la función execve()


# 🎯 TOKENIZACION (📁 lexer)

📋 Analizamos sintácticamente el input o prompt para tokenizarlo*.

*Tokens-> son unidades significativas para el lenguaje de rogramación, como palabras clave, identificadores, operadores, números, etc. 

## 🔧 Pasos a realizar

### ✅ Estructura (📁 lexer.h)
	type -> Tipo de token
		|-> T_WORD -> Palabra. Puede ser un comando, un archivo de entrada, de salida...
		|-> T_PIPE -> |
		|-> T_REDIR_IN -> <
		|-> T_HEREDOC -> <<
		|-> T_REDIR_OUT -> >
		|-> T_APPEND -> >>
	value -> string con el token
	single_quotes -> flag si value está entre comillas simples
	double_quotes -> flag si value está entre comillas dobles

❓ Que pasa si tenemos tanto comillas simples o dobles?

### ✅ Tokenización

#### 📁 lexer.c
	✅ Función lexer() -> manejo del flujo
		|-> Obvia los espacios
		|-> Verifica que tipo de token recibimos y crea la lista enlazada

	✅ Función handle_word() -> maneja si el token es una palabra y lanza el proceso para leer la palabra y añadir el nodo.
		|-> ♻️ Libero char *word -> ya lo he pasado a la función add_token(), que crea una copia de word y, por tanto, no lo necesito.

	✅ Función read_word() -> leo el input mientras no sea un espacio o un simbolo (|, <, >)
		|-> 🧠 Copiamos char *word con ft_substr

	✅ Función handle_redirection() -> Verifica que redirección es (<, <<, >, >>) y ejecuta add_token()

	✅ Función handle_quotes -> maneja si tenemos un token entre comillas simples o dobles
		|-> No tenemos comillas de cierre -> ⛔ Error
⚠️ Que hacemos si no tenemos comillas de cierre?
		|-> 🧠 Copiamos char *word con ft_substr
		|-> Ejecutamos add_token() para crear el nodo.
		|-> Flags single_quotes o double_quotes = 1
		|-> ♻️ Libero char *word

#### 📁 lexer_utils.c
	✅ Función new_token() -> Crea un nuevo nodo
		|-> 🧠 Copiamos value con ft_strdup

	✅ Función token_add_back () -> añade el nodo al final si no es el HEAD

	✅ Función add_token() -> maneja el flujo de creación y adición de nodos

	✅ Función free_tokens() -> ♻️ libera toda la lista enlazada.
		|-> ♻️ libera value

## ⚠️ Revisar 

#### 📁 lexer_conversion.c ⚠️

# 🎯 PARSEO (📁 parser)

📋 Parseamos los tokens y creamos una lista enlazada con los comandos a procesar y el nombre del archivo de entrada o de salida. Cada vez que tenemos un pipe ( | ), creamos un nuevo nodo.

## 🔧 Pasos a realizar

### ✅ Estructura (📁 parser.h)
	argv -> array de string de los comandos a ejecutar
	infile -> nombre del archivo de entrada
	outfile -> nombre del archivo de salida
	append -> flag si tenemos >>
	heredoc -> flag si tenemos <<

### ✅ Analizador de sintaxis (📁 syntax_check.c)

📋 Analiza los tokens y su orden para comprobar que la sintaxis es correcta. Por ejemplo, que no tenemos dos pipes seguidos en el input (ls | | grep)

	✅ Función validate_tokens() -> maneja el flujo y devuelve 
		|-> 0 (no válido) ⛔
		|-> 1 (válido)

	✅ Función is_pipe_first_token() -> Comprueba
		|-> primer token no es un pipe (|) ⛔

	✅ Función is_pipe_error () -> Comprueba
		|-> dos pipes seguidos || ⛔
		|-> último token es un pipe ⛔
		|-> pipe no seguido de una palabra (T_WORD) ⛔

	✅ Función is_redir_error() -> Comprueba
		|-> último token es una redirección ⛔
		|-> redirección no seguido de una palabra (T_WORD) ⛔

	✅ Función print_syntax_error() -> 🗒️ Imprime mensaje de error

### ✅ Parseo 

#### 📁 parser.c
	✅ Función parse_tokens() -> maneja el flujo del parseo
		|-> token == T_WORD -> añado a lista de comandos
		|-> token == T_PIPE -> Creamos nuevo nodo
		|-> token == Redirección -> Guardamos nombre de archivo

	✅ Función new_cmd() -> Creamos el nodo con los valores de la estructura inicializados a NULL o cero

	✅ Función cmd_add_back() -> Añado el nodo al final si no es el primero

	✅ Función add_to_argv() -> Crea dinamicamente un array de string para agregar los comandos al array
		|-> 🧠 Reservamos memoria para el nuevo array char**
		|-> Guardamos en el nuevo array lo que ya teniamos en el viejo
		|-> 🧠 Añadimos/copiamos el nuevo comando con ft_strdup
		|-> ♻️ liberamos el antiguo array char**

	✅ Función handle_redirection() -> maneja las redirecciones < << > >>
		|-> 🧠 Guarda el nombre del archivo de entrada o de salida con ft_strdup
		|-> flag si se trata de heredoc o append

#### 📁 parser_utils.c
	✅ Función is_redir() -> Verifica si se trata de una redirección < << > >>

	✅ Función free_array() -> ♻️ libera un char**

	✅ Función free_cmds -> ♻️ libera la lista enlazada t_cmd
		|-> ♻️ libera char **argv. La lista de comandos
		|-> ♻️ libera infile. Fue reservado con ft_strdup
		|-> ♻️ libera outfile. Fue reservado con ft_strdup


# 🎯 LIMPIEZA (📁 utils)

📋 Creación de funciones para centralizar la limpieza

#### 📁 cleanup_utils.c
	✅ Función cleanup_loop() -> Limpieza del bucle while(1) cada vez que lanzamos un prompt
		|-> ♻️ libera el input
		|-> ♻️ libera t_tokens
		|-> ♻️ libera t_cmd
		|-> Resetea punteros a NULL (recomendable)

	❌ Función close_fd() -> Cierre de filedescriptors

	✅ Función cleanup_shell() -> Limpieza final del programa
		|-> ♻️ cleanup_loop()
		|-> ♻️ libera t_env

#### 📁 error_utils.c
⚠️Pendiente de revisión
	❌ Función exit_error_cleanup() -> Exit, imprime ⛔ error y ♻️ libera

	❌ Función exit_cleanup() -> Exit y ♻️ libera

✅
⚠️
🚨
📋
♻️
🧠
❗
⛔
❌
🗒️