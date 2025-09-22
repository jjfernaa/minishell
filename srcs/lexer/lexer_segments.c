#include "lexer.h"

static int	*read_quoted_segment(const char *input, int *i, char **text, t_quote_type *quote_type)
{
	char	quote;
	int		start;

	*text = NULL;
	quote = input[*i];
	if (quote != '\'' && quote != '"')
		return (0);
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		write(STDERR_FILENO, "Error: missing closing quote\n", 29);
		return (0);
	}
	*text = ft_substr(input, start, *i - start);
	if (!*text)
		return (0);
	(*i)++;
	if (quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else if (quote == '"')
		*quote_type = DOUBLE_QUOTE;
	return (1);
}

static int	*read_noquoted_segment(const char *input, int *i, char **text)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	*text = ft_substr(input, start, *i - start);
	if (!*text)
		return (0);
	return (1);
}

int	*read_segment(const char *input, int *i, char **text, t_quote_type *quote_type)
{
	*text = NULL;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (!read_quoted_segment(input, i, text, quote_type))
			return (0);
		return (1);
	}
	*quote_type = NO_QUOTE;
	if (!read_noquoted_segment(input, i, text))
		return (0);
	return (1);
}
