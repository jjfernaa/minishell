#include "env.h"

static t_env	*new_env_node(const char *env_input)
{
	t_env	*node;
	char	*equal_pos;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(env_input, '=');
	if (!equal_pos)
	{
		free(node);
		return (NULL);
	}
	key_len = equal_pos - env_input;
	node->key = ft_substr(env_input, 0, key_len);
	node->value = ft_strdup(equal_pos + 1);
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
