
#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

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
	struct s_token	*next;
} t_token;

#endif