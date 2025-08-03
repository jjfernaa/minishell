#include "env.h"
// Eliminar y quedarnos solo con un free_array. Por ejemplo, crear un utils.h
static void	free_array_envp(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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

static char	*create_envp_line(t_env *env, char **envp)
{
	char	*joined_key_equal;
	char	*envp_line;

	joined_key_equal = ft_strjoin(env->key, "=");
	if (!joined_key_equal)
	{
		free_array_envp(envp);
		return (NULL);
	}
	envp_line = ft_strjoin(joined_key_equal, env->value);
	if (!envp_line)
	{
		free(joined_key_equal);
		free_array_envp(envp);
		return (NULL);
	}
	free(joined_key_equal);
	return (envp_line);
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
	while (env)
	{
		if (env->key && env->value)
		{
			envp[i] = create_envp_line(env, envp);
			if (!envp[i])
				return NULL;
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
