/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:38:17 by juan-jof          #+#    #+#             */
/*   Updated: 2025/07/31 22:30:56 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, shell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, shell));
	return (-1);
}

static void	execute_parser_command(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	char	**args;
	int		builtin_result;

	if (has_pipes_or_redirects(tokens))
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
		free_args(args);
	}
}

void	process_command(char *input, t_shell *shell)
{
	t_token	*tokens;

	tokens = lexer(input);
	if (!tokens)
		return ;
	if (!validate_tokens(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	execute_parser_command(tokens, shell);
	free_tokens(tokens);
}
