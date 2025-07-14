#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parse_tokens(t_token *tokens);

#endif
