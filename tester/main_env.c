#include "minishell.h"

void print_env(t_env *env)
{
	printf("\n==== LISTA VARIABLES ENTORNO ====\n\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env *env = init_env(envp);

	argc = 0;
	argv = NULL;
	if (!env)
		return (1);
	print_env(env); // ✅ Verifica que la lista se construyó bien
	free_env(env);
	return (0);
}
