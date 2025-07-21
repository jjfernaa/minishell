#include "minishell.h"

/* static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp; // Inicializar a NULL y reconstruir el array a partir de env
	shell->exit_status = 0;
	shell->env = init_env(envp);
	if (!shell->env)
	{
		printf("Error: Could not initialize environment\n");
		exit(1);
	}
}

/* int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

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
		shell->tokens = lexer(input);
		if(!validate_tokens(shell->tokens));
			exit_cleanup(shell, EXIT_FAILURE);
		shell->cmd = parse_tokens(shell->tokens);
		process_command(input, &shell);
		free(input);
	}
	return (shell->exit_status);
} */

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		exit_error_cleanup(shell, "minishell: error initializing environment\n", EXIT_FAILURE);
	//shell->envp = envp; // Inicializar a NULL y reconstruir el array a partir de env
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->infile_fd = -1;
	shell->outfile_fd = -1;
	shell->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	init_shell(shell, envp);
	setup_signals();
	while (1)
	{
		shell->input = readline("minishell$ ");
		if (!shell->input)
			exit_error_cleanup(shell, "exit\n", EXIT_FAILURE);
		add_history(shell->input);
		shell->tokens = lexer(shell->input);
		if(!validate_tokens(shell->tokens));
			exit_cleanup(shell, EXIT_FAILURE);
		shell->cmd = parse_tokens(shell->tokens);
		// Control errores cmds
		process_command(shell->input, &shell);
		cleanup_loop(shell);
	}
	rl_clear_history();
	cleanup_shell(shell);
	return (shell->exit_status);
}
