#include "lexer.h"

void	add_segment_to_token(t_token *token, const char *content, t_quote_type quote_type)
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

static char	*read_quoted_segment(const char *input, int *i, t_quote_type *quote_type)
{
	char	quote;
	char	*part;
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
	part = ft_substr(input, start, len);
	(*i)++;
	if (quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else if (quote == '"')
		*quote_type = DOUBLE_QUOTE;
	return (part);
}

static char	*read_unquoted_segment(const char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

char	*read_segment(const char *input, int *i, t_quote_type *quote_type)
{
	*quote_type = NO_QUOTE;
	if (input[*i] == '\'' || input[*i] == '"')
		return (read_quoted_segment(input, i, quote_type));
	else
		return (read_unquoted_segment(input, i));
}
