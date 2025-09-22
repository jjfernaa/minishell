#include "../../includes/minishell.h"

int	handle_redirection_error(int final_fd, char *filename)
{
	perror(filename);
	if (final_fd != -1)
		close(final_fd);
	return (-1);
}
