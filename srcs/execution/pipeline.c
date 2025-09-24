#include "../../includes/minishell.h"

static int	has_redirections(t_cmd *cmd)
{
	return (cmd->input_redirs || cmd->output_redirs || cmd->heredoc);
}

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
	int		builtin_result;

	if (preprocess_heredocs(cmds) == -1)
	{
		shell->exit_status = 130;
		return ;
	}
	cmd_count = count_commands(cmds);
	current = cmds;
	if (has_redirections(current) || cmd_count > 1)
	{
		execute_pipeline_real(cmds, shell);
		return ;
	}
	if (current->argv && current->argv[0])
	{
		builtin_result = execute_builtin(current->argv, shell);
		if (builtin_result == -1)
			shell->exit_status = execute_external(current->argv, shell);
		else
			shell->exit_status = builtin_result;
	}
}
