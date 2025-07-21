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

static void	handle_quotes(t_token **list, const char *input, int *i)
{
	char	quote;
	char	*word;
	int		start;
	int		len;
	t_token	*token;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		write(STDOUT_FILENO, "Syntax error: missing closing quote\n", 36);
		return ;
	}
	len = *i - start;
	word = ft_substr(input, start, len);
	token = add_token(list, T_WORD, word);
	if (quote == '\'')
		token->single_quotes = 1;
	else if (quote == '"')
		token->double_quotes = 1;
	free(word);
	(*i)++;
}

static char	*read_word(const char *input, int *i)
{
	char	*word;
	int		start;
	int		len;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i]))
		(*i)++;
	len = *i - start;
	word = ft_substr(input, start, len);
	return (word);
}

static void	handle_word(t_token **list, const char *input, int *i)
{
	char	*word;

	word = read_word(input, i);
	add_token(list, T_WORD, word);
	free(word);
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
		else if (input[i] == '\'' || input[i] == '\"')
			handle_quotes(&tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
	}
	return (tokens);
}
