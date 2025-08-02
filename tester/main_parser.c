#include "minishell.h"

void print_token_type(t_token_type type)
{
    if (type == T_WORD)
        printf("WORD");
    else if (type == T_PIPE)
        printf("PIPE");
    else if (type == T_REDIR_IN)
        printf("REDIR_IN");
    else if (type == T_REDIR_OUT)
        printf("REDIR_OUT");
    else if (type == T_APPEND)
        printf("APPEND");
    else if (type == T_HEREDOC)
        printf("HEREDOC");
    else
        printf("UNKNOWN");
}

void print_tokens(t_token *tokens)
{
    int i = 0;
    while (tokens)
    {
        printf("Token %d:\n", i++);
        printf("  Type: ");
        print_token_type(tokens->type);
        printf("\n  Value: \"%s\"\n", tokens->value);
        printf("  In single quotes: %s\n", tokens->single_quotes ? "YES" : "NO");
        printf("  In double quotes: %s\n\n", tokens->double_quotes ? "YES" : "NO");
        tokens = tokens->next;
    }
}

void	print_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds)
	{
		printf("---- Command %d ----\n", i);
		j = 0;
		if (cmds->argv)
		{
			while (cmds->argv[j])
			{
				printf("argv[%d]: %s\n", j, cmds->argv[j]);
				j++;
			}
		}
		if (cmds->infile)
			printf("infile: %s%s\n", cmds->infile, cmds->heredoc ? " (HEREDOC)" : " (REDIR_IN)");
		if (cmds->outfile)
			printf("outfile: %s%s\n", cmds->outfile, cmds->append ? " (APPEND)" : " (REDIR_OUT)");
		cmds = cmds->next;
		i++;
	}
}

void	free_cmds(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		t_cmd *tmp = cmds;
		i = 0;
		if (cmds->argv)
		{
			while (cmds->argv[i])
			{
				free(cmds->argv[i]);
				i++;
			}
			free(cmds->argv);
		}
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		cmds = cmds->next;
		free(tmp);
	}
}

int main(void)
{
	const char	*input = "cat < input.txt | grep hola >> salida.txt";
	t_token 	*tokens = lexer(input);
	t_cmd 		*cmds;

	if (!tokens)
	{
		printf("Error: lexer failed\n");
		return (1);
	}
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		printf("Error: parser failed\n");
		free_tokens(tokens);
		return (1);
	}
	printf("==== TOKENS ====\n");
	print_tokens(tokens); // esta función debe estar en tu lexer

	printf("==== COMANDOS PARSEADOS ====\n");
	print_cmds(cmds);

	free_tokens(tokens);
	free_cmds(cmds);
	return (0);
}
