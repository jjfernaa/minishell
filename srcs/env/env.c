#include "env.h"

static t_env	*new_env_node(const char *env_input)
{
	t_env	*node;
	char	*equal_pos;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(env_input, '='); //Buscamos la posicion del signo '='
	if (!equal_pos)
	{
		free(node);
		return (NULL);
	}
	key_len = equal_pos - env_input;
	node->key = ft_substr(env_input, 0, key_len);
	node->value = ft_strdup(equal_pos + 1); //Esto copia desde la posicion del '=' + 1
	node->next = NULL;
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

static void	env_add_back(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
		{
			free_env(env);
			return (NULL);
		}
		env_add_back(&env, new_node);
		i++;
	}
	return (env);
}
// Opción 2 para init_env(), donde la complejidad en tiempo es O(1)
// al no tener que iterar por toda la lista cada vez que añadimos un nodo.
/* t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*last;
	t_env	*new_node;
	int		i;

	env = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
		{
			free_env(env);
			return (NULL);
		}
		if (!new_node)
			env = new_node; // primer nodo (head de la lista)
		else
			last->next = new_node; // si hay head, hacemos que el ultimo nodo apunte al nuevo, que sería el último.
		last = new; //Actualizamos last para que el nuevo nodo sea el ultimo.
		i++;
	}
	return (env);
} */
