#include "parser.h"

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_REDIR_IN || token->type == T_HEREDOC 
		|| token->type == T_REDIR_OUT || token->type == T_APPEND)
		return (1);
	return (0);
}
