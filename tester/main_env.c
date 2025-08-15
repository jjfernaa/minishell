#include "minishell.h"

void	print_env(t_env *env)
{
	printf("\n==== LISTA VARIABLES ENTORNO ====\n\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = init_env(envp);
	(void)argc;
	(void)argv;
	if (!env)
		return (1);
	print_env(env);
	free_env(env);
	return (0);
}
