#include "../../includes/minishell.h"

int	has_pipes_or_redirects(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE || is_redir(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	int		cmd_count;
	int		builtin_result;//duda de inicializacion

	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
	{
		current = cmds;
		if (current->argv && current->argv[0])
		{
			builtin_result = execute_builtin(current->argv, shell);
			if (builtin_result == -1)
				shell->exit_status = execute_external(current->argv, shell);
			else
				shell->exit_status = builtin_result;
		}
	}
	else
	{
		execute_pipeline_real(cmds, shell);
	}
}
