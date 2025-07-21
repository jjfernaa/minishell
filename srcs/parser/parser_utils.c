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

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
		free(tmp);
	}
}
