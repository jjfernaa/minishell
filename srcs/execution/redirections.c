#include "../../includes/minishell.h"

static int	create_heredoc_pipe(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	open_redirection_file(t_redir *redir)
{
	int	flags;

	if (redir->type == T_HEREDOC)
		return (create_heredoc_pipe(redir->filename));
	else if (redir->type == T_REDIR_IN)
		return (open(redir->filename, O_RDONLY));
	else
	{
		flags = O_CREAT | O_WRONLY;
		if (redir->type == T_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		return (open(redir->filename, flags, 0644));
	}
}

static int	process_input_redirections(t_redir *input_redirs)
{
	t_redir	*current;
	int		fd;
	int		final_fd;

	current = input_redirs;
	final_fd = -1;
	while (current)
	{
		fd = open_redirection_file(current);
		if (fd < 0)
			return (handle_redirection_error(final_fd, current->filename));
		if (final_fd != -1)
			close(final_fd);
		final_fd = fd;
		current = current->next;
	}
	if (final_fd != -1)
	{
		dup2(final_fd, STDIN_FILENO);
		close(final_fd);
	}
	return (0);
}

static int	process_output_redirection(t_redir *output_redirs)
{
	t_redir	*current;
	int		fd;
	int		final_fd;

	current = output_redirs;
	final_fd = -1;
	while (current)
	{
		fd = open_redirection_file(current);
		if (fd < 0)
			return (handle_redirection_error(final_fd, current->filename));
		if (current->next)
			close(fd);
		else
			final_fd = fd;
		current = current->next;
	}
	if (final_fd != -1)
	{
		dup2(final_fd, STDOUT_FILENO);
		close(final_fd);
	}
	return (0);
}

void	apply_redirections(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->input_redirs)
	{
		if (process_input_redirections(cmd->input_redirs) != 0)
			exit(1);
	}
	if (cmd->output_redirs)
	{
		if (process_output_redirection(cmd->output_redirs) != 0)
			exit(1);
	}
}

