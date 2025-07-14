#include "env.h"

static t_env	*new_env_node(const char *env_input)
{
	t_env	*node;
	char	*equal_pos;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(env_input, '='); //Buscamos la posicion del signo =
	if (!equal_pos)
	{
		free(node);
		return (NULL);
	}
	key_len = equal_pos - env_input;
	node->key = ft_substr(env_input, 0, key_len);
	node->value = ft_strdup(equal_pos + 1); //Esto copia desde la posicion del = + 1
	node->next = NULL;
	return (node);
}
