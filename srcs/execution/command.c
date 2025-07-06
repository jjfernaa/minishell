/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:38:17 by juan-jof          #+#    #+#             */
/*   Updated: 2025/07/06 03:48:37 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_builtin(char **args, t_shell *shell)
{
	if (strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (strcmp(args[0], "env") == 0)
		return (builtin_env(shell));
	else if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell));
	else if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, shell));
	return (-1);
}

void	process_command(char *input, t_shell *shell)
{
	char	**args;
	int		builtin_result;

	args = split_input(input);
	if (!args)
		return ;
	builtin_result = execute_builtin(args, shell);
	if (builtin_result == -1)
		printf("Has escrito: '%s'\n", input);
	free_args(args);
}
