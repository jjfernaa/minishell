#include "minishell.h"

int	execute_builtin(char **args, t_shell *shell)
{
 	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, shell));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, shell));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, shell));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, shell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, shell));
	return (-1);
}

static void	execute_parser_command(t_shell *shell)
{
	t_cmd	*cmds;
	t_token *tokens;
	char	**args;
	int		builtin_result;

	tokens = shell->tokens;
	if (has_pipes_or_redirects(shell->tokens))
	{
		cmds = parse_tokens(tokens);
		execute_pipeline(cmds, shell);
		free_cmds(cmds);
	}
	else
	{
		args = tokens_to_args(tokens);
		builtin_result = execute_builtin(args, shell);
		if (builtin_result == -1)
			shell->exit_status = execute_external(args, shell);
		else
			shell->exit_status = builtin_result;
		free_array(args);
	}
}

void	process_command(t_shell *shell)
{
	shell->tokens = lexer(shell->input);
	if (!shell->tokens)
	{
		shell->exit_status = 2;
		return ;
	}
	expand_var(shell);
	if (!validate_tokens(shell->tokens))
	{
		shell->exit_status = 2;
		return ;
	}
	execute_parser_command(shell);
}
