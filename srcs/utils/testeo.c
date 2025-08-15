#include "minishell.h"

//Testeo

void	print_token_type(t_token_type type)
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

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token %d:\n", i++);
		printf("  Type: ");
		print_token_type(tokens->type);
		printf("\n  Value: \"%s\"\n", tokens->value);
		printf("  quotes_type: %u\n", tokens->quote_type);
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

void	print_env(t_env *env)
{
	printf("\n==== LISTA VARIABLES ENTORNO ====\n\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
