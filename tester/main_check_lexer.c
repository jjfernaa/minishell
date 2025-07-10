#include "minishell.h"
#include <stdio.h>

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

int main(void)
{
    const char *input = "echo 'hola $USER' | cat << fin >> out.txt \"adios mundo\"";
    t_token *tokens = lexer(input);

    print_tokens(tokens);
    free_tokens(tokens);
    return 0;
}
