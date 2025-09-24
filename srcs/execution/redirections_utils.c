#include "../../includes/minishell.h"

int	handle_redirection_error(int final_fd, char *filename, t_token_type type)
{
	if (type == T_HEREDOC)
		return (-2);
	perror(filename);
	if (final_fd != -1)
		close(final_fd);
	return (-1);
}

int	preprocess_heredocs(t_cmd *cmds)
{
	t_cmd	*current;
	t_redir	*redir;
	int		fd;

	current = cmds;
	while (current)
	{
		redir = current->input_redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				fd = create_heredoc_pipe(redir->filename);
				if (fd == -1)
					return (-1);// Heredoc cancelado
				// Guardar el fd para usar después
				redir->heredoc_fd = fd;
				redir->type = T_REDIR_IN;// Cambiar a redirección normal
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

/* función que lee línea por línea hasta el delimiter */
int	handle_heredoc_input(int *pipefd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDERR_FILENO, "\n", 1);
			close(pipefd[1]);
			close(pipefd[0]);
			return (-1);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	return (0);
}
