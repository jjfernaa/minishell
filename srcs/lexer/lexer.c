#include "lexer.h"

/* static void	handle_redirection(t_token **list, const char *input, int *i)
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
		write(STDERR_FILENO, "Syntax error: missing closing quote", 36);
		return ;
	}
	len = *i - start;
	word = ft_substr(input, start, len);
	token = add_token(list, T_WORD, word);
	if (quote == '\'')
		token->quote_type = SINGLE_QUOTE;
	else if (quote == '"')
		token->quote_type = DOUBLE_QUOTE;
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
} */

/* static void	handle_redirection(t_token **list, const char *input, int *i)
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

static char	*read_quoted_string(const char *input, int *i)
{
	char	quote;
	char	*word;
	int		start;
	int		len;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		write(STDERR_FILENO, "Error: missing closing quote\n", 29);
		return (ft_strdup(""));
	}
	len = *i - start;
	word = ft_substr(input, start, len);
	(*i)++;
	return (word);
}

static char	*read_word_part(const char *input, int *i)
{
	char	*result;
	char	*temp;
	char	*part;
	int		start;

	result = ft_strdup("");
	while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			part = read_quoted_string(input, i);
		else
		{
			start = *i;
			while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i])
				&& input[*i] != '\'' && input[*i] != '"')
				(*i)++;
			part = ft_substr(input, start, *i - start);
		}
		temp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = temp;
	}
	return (result);
}

static void	handle_word(t_token **list, const char *input, int *i)
{
	char	*word;

	word = read_word_part(input, i);
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
		else
			handle_word(&tokens, input, &i);
	}
	return (tokens);
} */
#include "lexer.h"
/* #include "lexer.h"

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

static void	add_segment_to_token(t_token *token, const char *content, t_quote_type quote_type)
{
    t_token_segment	*new_segment;
    t_token_segment	*current;

    new_segment = malloc(sizeof(t_token_segment));
    if (!new_segment)
        return ;
    new_segment->content = ft_strdup(content);
    new_segment->quote_type = quote_type;
    new_segment->next = NULL;
    if (!token->segments)
        token->segments = new_segment;
    else
    {
        current = token->segments;
        while (current->next)
            current = current->next;
        current->next = new_segment;
    }
}

static void	handle_word_with_concatenation(t_token **list, const char *input, int *i)
{
    char			*result;
    char			*temp;
    char			*part;
    t_quote_type	quote_type;
    t_quote_type	part_quote_type;
    int				first_token;
    t_token			*token;

    quote_type = NO_QUOTE;
    first_token = 1;
    result = ft_strdup("");
    token = add_token(list, T_WORD, "");
    while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i]))
    {
        part_quote_type = NO_QUOTE;
        if (input[*i] == '\'' || input[*i] == '"')
        {
            char	quote = input[*i];
            int		start = ++(*i);
            int		len;

            while (input[*i] && input[*i] != quote)
                (*i)++;
            if (input[*i] != quote)
            {
                write(STDERR_FILENO, "Error: missing closing quote\n", 29);
                free(result);
                return ;
            }
            len = *i - start;
            part = ft_substr(input, start, len);
            (*i)++;
            if (quote == '\'')
                part_quote_type = SINGLE_QUOTE;
            else if (quote == '"')
                part_quote_type = DOUBLE_QUOTE;
        }
        else
        {
            int	start = *i;

            while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i])
                && input[*i] != '\'' && input[*i] != '"')
                (*i)++;
            part = ft_substr(input, start, *i - start);
            part_quote_type = NO_QUOTE;
        }
        add_segment_to_token(token, part, part_quote_type);
        if (first_token)
        {
            quote_type = part_quote_type;
            first_token = 0;
        }
        temp = ft_strjoin(result, part);
        free(result);
        free(part);
        result = temp;
        if (!result)
            return ;
    }
    if (token)
    {
        free(token->value);
        token->value = result;
        token->quote_type = quote_type;
    }
    else
        free(result);
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
 */
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
