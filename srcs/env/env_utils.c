#include "env.h"

t_env	*find_env_var(t_env *env_list, const char *key)
{
	if (!key)
		return (NULL);
	while (env_list)
	{
		if (env_list->key && ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	update_env_var(t_env *env_var, const char *value)
{
	char	*new_value;

	if (!env_var || !value)
		return ;
	new_value = ft_strdup(value);
	if (!new_value)
		return ;
	free (env_var->value);
	env_var->value = new_value;
}

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	if (!key)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free_env_node(new_node);
		return (NULL);
	}
	return (new_node);
}

void	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*existing;
	t_env	*new_node;

	if (!env_list || !key)
		return ;
	existing = find_env_var(*env_list, key);
	if (existing)
	{
		update_env_var(existing, value);
		return ;
	}
	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	new_node->next = *env_list;
	*env_list = new_node;
}

// Utilizamos find_env_var en lugar de ésta
/* char	*get_env_value_list(t_env *env, const char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
} */
