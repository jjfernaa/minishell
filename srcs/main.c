#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		exit_error_cleanup(shell, "minishell: error initializing environment\n", EXIT_FAILURE);
	shell->envp = envp; // Inicializar a NULL y reconstruir el array a partir de env
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->infile_fd = -1;
	shell->outfile_fd = -1;
	shell->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_command(input, &shell);
		free(input);
		cleanup_loop(&shell);
	}
	rl_clear_history();
	cleanup_shell(&shell);
	return (shell.exit_status);
}
