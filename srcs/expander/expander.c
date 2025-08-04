#include "minishell.h"

static void	append_exit_status(char **result, int exit_status)
{
	char	*exit_status_str;
	char	*new_str;

	// Convertimos el número a string
	exit_status_str = ft_itoa(exit_status);
	if (!exit_status_str)
		return ;
	// Concatenamos al resultado actual
	new_str = ft_strjoin(*result, exit_status_str);
	free(exit_status_str);
	if (!new_str)
		return ;
	// Liberamos el resultado anterior y actualizamos
	free(*result);
	*result = new_str;
}

static void	append_char(char **result, char c)
{
	char	*new_str;
	size_t	len;

	if (!result || !*result)
		return ;
	len = ft_strlen(*result);
	new_str = malloc(len + 2);
	if (!new_str)
		return ;
	ft_memcpy(new_str, *result, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(*result); // Liberamos el anterior
	*result = new_str; // Actualizamos el puntero
}

static void	append_env_var(char **result, const char *str, t_env *env, int *i)
{
	int		len;
	char	*new_string;
	char	*var_name;
	char	*value;

	// Leer nombre de variable
	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	// Extraer nombre (ej: "USER")
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return ;
	// Buscar valor en env
	value = get_env_value(env, var_name);
	free(var_name);
	// Si no se encuentra, no añadimos nada
	if (!value)
	{
		*i += len;
		return ;
	}
	// Concatenar al resultado actual
	new_string = ft_strjoin(*result, value);
	if (!new_string)
		return ;
	free(*result);
	*result = new_string;
	*i += len;
}

static char	*expand_string(const char *str, t_env *env, int exit_status)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				append_exit_status(&result, exit_status);
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				append_env_var(&result, str + i + 1, env, i);
			else
				append_char(&result, str[i++]);
		}
		else
			append_char(&result, str[i++]);
	}
	return (result);
}

void	expand_var(t_token *tokens, t_env *env, int exit_status)
{
	while (tokens)
	{
		if(tokens->type == T_WORD
			&& tokens->quote_type != SINGLE_QUOTE)
			tokens->value = expand_string(tokens->value, env, exit_status);
	}
	tokens = tokens->next;
}
