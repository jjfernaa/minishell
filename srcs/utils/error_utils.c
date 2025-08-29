#include "minishell.h"

void	print_cmd_not_found(const char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 21);
}

void	exit_error_cleanup(t_shell *shell, char *message, int code)
{
	if (message)
		perror(message);
	cleanup_shell(shell);
	exit(code);
}
