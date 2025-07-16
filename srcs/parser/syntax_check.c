#include "parser.h"

void	print_syntax_error(t_token *token)
{
	
}

int	validate_tokens(t_token *token)
{
	t_token	*prev_token;

	prev_token = NULL;
	if (!token || token->type == T_PIPE) //Primer token es pipe
		return (0);
	while (token)
	{
		if (token->type == T_PIPE) //Tengo dos pipes seguidos ||
		{
			if (!token->next || token->next->type != T_WORD)
				return (0);
		}
		if (is_redirection(token) // Redirección 
			&& (!token->next || token->next->type != T_WORD))
			return (0);
		prev_token = token;
		token = token->next;
	}
	if (prev_token && prev_token->type == T_PIPE) //Ultimo token es pipe
		return (0);
	return (1);
}
