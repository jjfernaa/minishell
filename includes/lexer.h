#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "utils.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote_type;

typedef struct s_token_segment
{
    char                    *text;
    t_quote_type           quote_type;
    struct s_token_segment *next;
} t_token_segment;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote_type;
	t_token_segment	*segments;
	struct s_token	*next;
}	t_token;

t_token	*lexer(const char *input);
int	read_segment(const char *input, int *i, char **text, t_quote_type *quote_type);

// Utils
t_token	*add_token(t_token **list, t_token_type type);
void	free_tokens(t_token *tokens);
int		add_segment_to_token(t_token *token, const char *value, t_quote_type quote_type);
void	free_segments(t_token_segment *segments);

// Conversion
char	**tokens_to_args(t_token *tokens);

#endif
