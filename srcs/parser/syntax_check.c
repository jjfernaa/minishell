#include "parser.h"

static void	print_syntax_error(t_token *token)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	if (!token)
		write(STDERR_FILENO, "newline", 7);
	else if (token->type == T_PIPE)
		write(STDERR_FILENO, "|", 1);
	else if (token->type == T_REDIR_IN)
		write(STDERR_FILENO, "<", 1);
	else if (token->type == T_REDIR_OUT)
		write(STDERR_FILENO, ">", 1);
	else if (token->type == T_HEREDOC)
		write(STDERR_FILENO, "<<", 2);
	else if (token->type == T_APPEND)
		write(STDERR_FILENO, ">>", 2);
	else if (token->value)
		write(STDERR_FILENO, token->value, ft_strlen(token->value));
	else
		write(STDERR_FILENO, "?", 1);
	write(STDERR_FILENO, "'\n", 2);
}

static int	is_pipe_first_token(t_token *token)
{
	if (token->type == T_PIPE)
	{
		print_syntax_error(token);
		return (1);
	}
	return (0);
}

static int	is_pipe_error(t_token *token)
{
	if (token->next->type == T_PIPE)
	{
		print_syntax_error(token);
		return (1);
	}
	else if (!token->next || token->next->type != T_WORD)
	{
		print_syntax_error(NULL);
		return (1);
	}
	return (0);
}

static int	is_redir_error(t_token *token)
{
	if (!token->next || token->next->type != T_WORD)
	{
		print_syntax_error(token);
		return (1);
	}
	return (0);
}

int	validate_tokens(t_token *token)
{
	if (!token)
		return (0);
	if (is_pipe_first_token(token))
		return (0);
	while (token)
	{
		if (token->type == T_PIPE)
		{
			if (is_pipe_error(token))
				return (0);
		}
		else if (is_redir(token))
		{
			if (is_redir_error(token))
				return (0);
		}
		token = token->next;
	}
	return (1);
}
