#include "lexer.h"

static int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	add_token(t_token **list, t_token_type type, const char *value)
{

}

static char	*read_word(const char *input, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;

	while (str[i])
	{

	}
	return (word);
}

t_token	*lexer(const char *input)
{
	t_token	*tokens = NULL;
	char	*word;
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, T_PIPE, "|");
			i++;
		}
		else
		{
			word = read_word(input, &i);
			add_token(&tokens, T_WORD, word);
			free(word);
		}
	}
	return (tokens);
}
