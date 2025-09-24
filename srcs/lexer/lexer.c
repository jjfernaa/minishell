#include "lexer.h"

static void	handle_redirection(t_token **list, const char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>' && input[*i + 1] != '\0')
	{
		add_token(list, T_APPEND);
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<' && input[*i + 1] != '\0')
	{
		add_token(list, T_HEREDOC);
		*i += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(list, T_REDIR_OUT);
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token(list, T_REDIR_IN);
		(*i)++;
	}
}

static int	handle_word(t_token **list, const char *input, int *i)
{
	t_token			*token;
	char			*result;
	t_quote_type	quote_type;

	token = add_token(list, T_WORD);
	if (!token)
		return (0);
	while (input[*i] && !ft_isspace((unsigned char)input[*i]) && !is_symbol(input[*i]))
	{
		result = NULL;
		if (!read_segment(input, i, &result, &quote_type))
			return (0);
		if (result)
		{
			if (!add_segment_to_token(token, result, quote_type))
			{
				free(result);
				return (0);
			}
			free(result);
		}
	}
	return (1);
}

t_token	*lexer(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace((unsigned char)input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, T_PIPE);
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			handle_redirection(&tokens, input, &i);
		else
		{
			if (!handle_word(&tokens, input, &i))
				return (NULL);
		}
	}
	return (tokens);
}
