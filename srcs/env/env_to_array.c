#include "env.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->key && env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		size;
	int		i;
	char	*joined_key_equal;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while(env)
	{
		if (env->key && env->value)
		{
			joined_key_equal = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(joined_key_equal, env->value);
			free(joined_key_equal);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
