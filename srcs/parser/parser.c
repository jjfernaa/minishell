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

static void	cmd_add_back(t_cmd **cmd_list, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmd_list)
	{
		*cmd_list = new;
		return;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*parse_tokens(t_token *tokens)
{

}
