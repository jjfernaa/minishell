/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:26:09 by juan-jof          #+#    #+#             */
/*   Updated: 2025/08/12 18:36:15 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	builtin_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
} */

int	builtin_env(char **args, t_shell *shell)
{
	t_env	*current;

	if (!shell || !shell->env)
		return (1);
	if (args && args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	current = shell->env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
