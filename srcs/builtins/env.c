/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:26:09 by juan-jof          #+#    #+#             */
/*   Updated: 2025/08/29 20:34:52 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, t_shell *shell)
{
	t_env	*current;

	if (args[1])
	{
		write(STDERR_FILENO, "env: too many arguments\n", 24);
		return (1);
	}
	if (!shell || !shell->env)
		return (1);
	current = shell->env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
