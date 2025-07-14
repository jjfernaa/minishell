#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
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
	}
	return (shell.exit_status);
}
