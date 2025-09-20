#include "lexer.h"

static void	handle_redirection(t_token **list, const char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(list, T_APPEND, ">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(list, T_HEREDOC, "<<");
		*i += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(list, T_REDIR_OUT, ">");
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token(list, T_REDIR_IN, "<");
		(*i)++;
	}
}

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, T_PIPE, "|");
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			handle_redirection(&tokens, input, &i);
		else
			handle_word_with_concatenation(&tokens, input, &i);
	}
	return (tokens);
}
