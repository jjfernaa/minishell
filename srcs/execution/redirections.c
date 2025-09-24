/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:25:28 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:44:56 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_redirection_file(t_redir *redir)
{
	int	flags;

	if (redir->type == T_HEREDOC)
		return (create_heredoc_pipe(redir->filename));
	else if (redir->type == T_REDIR_IN)
	{
		if (redir->heredoc_fd != -1)
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
			exit(130);
		else if (result != 0)
			exit(1);
	}
	if (cmd->output_redirs)
	{
		if (process_output_redirection(cmd->output_redirs) != 0)
			exit(1);
	}
}
