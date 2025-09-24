/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:27:15 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:27:16 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
	{
		write(2, "minishell: error initializing environment\n", 42);
		cleanup_shell(shell);
		exit(EXIT_FAILURE);
	}
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->infile_fd = -1;
	shell->outfile_fd = -1;
	shell->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.input = readline("minishell$ ");
		if (!shell.input)
		{
			printf("exit\n");
			break ;
		}
		if (*shell.input)
			add_history(shell.input);
		process_command(&shell);
		cleanup_loop(&shell);
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
