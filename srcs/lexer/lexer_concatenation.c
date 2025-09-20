#include "lexer.h"
#include "../../includes/minishell.h"

static void	update_token_quote_type(t_token *token, t_quote_type part_quote_type, int is_first)
{
	if (is_first)
		token->quote_type = part_quote_type;
}

static char	*concatenate_part(char *result, const char *part)
{
	char	*temp;

	temp = ft_strjoin(result, part);
	free(result);
	return (temp);
}

static int	process_segment(t_token *token, const char *input, int *i, char **result, int *first_token)
{
	char			*part;
	t_quote_type	part_quote_type;

	part = read_segment(input, i, &part_quote_type);
	if (!part)
		return (0);
	add_segment_to_token(token, part, part_quote_type);
	update_token_quote_type(token, part_quote_type, *first_token);
	*first_token = 0;
	*result = concatenate_part(*result, part);
	free(part);
	return (*result != NULL);
}

void	handle_word_with_concatenation(t_token **list, const char *input, int *i)
{
	char	*result;
	t_token	*token;
	int		first_token;

	result = ft_strdup("");
	token = add_token(list, T_WORD, "");
	first_token = 1;
	while (input[*i] && !ft_isspace(input[*i]) && !is_symbol(input[*i]))
	{
		if (!process_segment(token, input, i, &result, &first_token))
		{
			free(result);
			return ;
		}
	}
	if (token)
	{
		free(token->value);
		token->value = result;
	}
	else
		free(result);
}
