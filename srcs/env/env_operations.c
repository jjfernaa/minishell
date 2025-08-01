#include "../../includes/minishell.h"

static void	remove_first_env_node(t_env **env_list)
{
	t_env	*current;

	current = *env_list;
	*env_list = (*env_list)->next;
	free(current->key);
	free(current->value);
	free(current);
}

void	remove_env_var(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*env_list)
		return ;
	if (ft_strcmp((*env_list)->key, key) == 0)
	{
		remove_first_env_node(env_list);
		return ;
	}
	prev = *env_list;
	current = (*env_list)->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
