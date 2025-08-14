#include "env.h"

void	remove_env_var(t_env **env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return ;
	current = *env_list;
	if (current->key && ft_strcmp(current->key, key) == 0)
	{
		*env_list = current->next;
		free_env_node(current);
		return ;
	}
	while (current->next)
	{
		if (current->next->key && ft_strcmp(current->key, key) == 0)
		{
			prev = current->next;
			current->next = current->next->next;
			free_env_node(prev);
			return ;
		}
		current = current->next;
	}
}
