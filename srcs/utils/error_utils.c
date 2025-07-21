#include "minishell.h"

void	exit_error_cleanup(t_shell *shell, char *message, int code)
{
	perror(message);
	cleanup_shell(shell);
	exit(code);
}

void	exit_cleanup(t_shell *shell, int code)
{
	cleanup_shell(shell);
	exit(code);
}
