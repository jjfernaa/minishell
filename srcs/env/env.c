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
	return (node);
}

static void	env_add_back(t_env **list, t_env *new)
{
	t_env	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
		{
			free_env(env);
			return (NULL);
		}
		env_add_back(&env, new);
		i++;
	}
	return (env);
}
