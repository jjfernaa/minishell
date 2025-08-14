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

static char	*create_envp_line(const char *key, const char *value)
{
	char	*joined_key_equal;
	char	*envp_line;

	joined_key_equal = ft_strjoin(key, "=");
	if (!joined_key_equal)
		return (NULL);
	envp_line = ft_strjoin(joined_key_equal, value);
	free(joined_key_equal);
	return (envp_line);
}

static void	free_envp_error(char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		size;
	int		i;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env && i < size)
	{
		if (env->key && env->value)
		{
			envp[i] = create_envp_line(env->key, env->value);
			if (!envp[i])
			{
				free_envp_error(envp, i);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
