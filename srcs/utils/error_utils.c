#include "minishell.h"

void	exit_error_cleanup(t_shell *shell, char *message, int code)
{
	if (message)
		perror(message);
	cleanup_shell(shell);
	rl_clear_history();
	exit(code);
}
