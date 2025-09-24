/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:31:07 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:31:08 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_loop(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmd)
		free_cmds(shell->cmd);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	cleanup_loop(shell);
	if (shell->env)
		free_env(shell->env);
	rl_clear_history();
}
