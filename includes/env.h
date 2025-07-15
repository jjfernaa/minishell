#ifndef ENV_H
# define ENV_H

#include "stdlib.h"
#include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*init_env(char **envp);
void	free_env(t_env *env);

#endif
