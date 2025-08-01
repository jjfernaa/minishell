#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
//# include "minishell.h"

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

int		validate_tokens(t_token *token);
t_cmd	*parse_tokens(t_token *tokens);

int		is_redir(t_token *token);
void	free_array(char **array);
void	free_cmds(t_cmd *cmd);

#endif
