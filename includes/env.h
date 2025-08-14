#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Basic
t_env	*init_env(char **envp);
void	free_env_node(t_env *node);
void	free_env(t_env *env);

// Utils
t_env	*find_env_var(t_env *env_list, const char *key);
void	update_env_var(t_env *env_var, const char *value);
t_env	*create_env_node(const char *key, const char *value);
void	add_env_var(t_env **env_list, char *key, char *value);

// Operations
void	remove_env_var(t_env **env_list, const char *key);

// Use just before execve to recompose environment variables
char	**env_to_array(t_env *env);

#endif
