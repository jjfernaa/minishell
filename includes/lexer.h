
#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef enum e_token_type
{
	T_WORD,			// Palabra
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_APPEND,		// >>
	T_HEREDOC		// <<
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				single_quotes;
	int				double_quotes;
	struct s_token	*next;
} t_token;

t_token	*lexer(const char *input);

// Utils
int		is_symbol(char c);
t_token	*add_token(t_token **list, t_token_type type, const char *value);
void	free_tokens(t_token *tokens);

#endif
