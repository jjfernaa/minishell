#include "parser.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	return (cmd);
}

static void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*cmd_list)
	{
		*cmd_list = new_node;
		return ;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static char	**add_to_argv(char **argv, char *word)
{
	char	**new_argv;
	int		i;
	int		len;

	len = 0;
	while (argv && argv[len])
		len++;
	new_argv = malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(word);
	new_argv[i] = NULL;
	free(argv);
	return (new_argv);
}

static void	handle_redirection(t_token *tokens, t_cmd *current)
{
	if (tokens->type == T_REDIR_IN || tokens->type == T_HEREDOC)
	{
		current->infile = ft_strdup(tokens->next->value);
		if (tokens->type == T_HEREDOC)
			current->heredoc = 1;
	}
	else if (tokens->type == T_REDIR_OUT || tokens->type == T_APPEND)
	{
		current->outfile = ft_strdup(tokens->next->value);
		if (tokens->type == T_APPEND)
			current->append = 1;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current_cmd;

	cmds = NULL;
	current_cmd = new_cmd();
	while (tokens)
	{
		if (tokens->type == T_WORD)
			current_cmd->argv = add_to_argv(current_cmd->argv, tokens->value);
		else if (tokens->type == T_PIPE)
		{
			cmd_add_back(&cmds, current_cmd);
			current_cmd = new_cmd();
		}
		else if (is_redir(tokens))
		{
			handle_redirection(tokens, current_cmd);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	cmd_add_back(&cmds, current_cmd);
	return (cmds);
}
