#include "parser.h"

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_REDIR_IN || token->type == T_HEREDOC
		|| token->type == T_REDIR_OUT || token->type == T_APPEND)
		return (1);
	return (0);
}

t_redir	*new_redir(char *filename, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = ft_strdup(filename);
	redir->type = type;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **redir_lis, char *filename, int type)
{
	t_redir	*new_redir_node;
	t_redir	*current;

	new_redir_node = new_redir(filename, type);
	if (!new_redir_node)
		return ;
	if (!*redir_lis)
	{
		*redir_lis = new_redir_node;
		return ;
	}
	current = *redir_lis;
	while (current->next)
		current = current->next;
	current->next = new_redir_node;
}

static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->argv)
			free_array(tmp->argv);
		free_redirs(tmp->input_redirs);
		free_redirs(tmp->output_redirs);
		free(tmp);
	}
}
