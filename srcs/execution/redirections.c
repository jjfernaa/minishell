#include "../../includes/minishell.h"

int	create_heredoc_pipe(char *delimiter)
{
	int		pipefd[2];
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	signal(SIGINT, SIG_DFL);
	if (handle_heredoc_input(pipefd, delimiter) == -1)
	{
		setup_signals();
		return (-1);
	}
	close(pipefd[1]);
	setup_signals();
	return (pipefd[0]);
}

static int	open_redirection_file(t_redir *redir)
{
	int	flags;

	if (redir->type == T_HEREDOC)
		return (create_heredoc_pipe(redir->filename));
	else if (redir->type == T_REDIR_IN)
	{
		if ( redir->heredoc_fd != -1)
			return (redir->heredoc_fd);
		return (open(redir->filename, O_RDONLY));
	}
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
			return (handle_redirection_error(final_fd, current->filename,
						current->type));
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
			return (handle_redirection_error(final_fd, current->filename,
						current->type));
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
	int	result;

	if (!cmd)
		return ;
	if (cmd->input_redirs)
	{
		result = process_input_redirections(cmd->input_redirs);
		if (result == -2)
			exit (130);
		else if (result != 0)
			exit(1);
	}
	if (cmd->output_redirs)
	{
		if (process_output_redirection(cmd->output_redirs) != 0)
			exit(1);
	}
}

