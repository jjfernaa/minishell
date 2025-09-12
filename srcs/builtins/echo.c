/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:22:48 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/12 22:37:36 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_n_flag(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	i = 1;
	newline = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
