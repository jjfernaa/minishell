/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce <dponce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:06:11 by juan-jof          #+#    #+#             */
/*   Updated: 2025/08/12 21:47:54 by dponce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* int	builtin_exit(char **args, t_shell *shell)
{
	printf("exit\n");
	if (!shell || !args || !args[1])
	{
		exit(shell->exit_status);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(ft_atoi(args[1]));
} */

int	builtin_exit(char **args, t_shell *shell)
{
	printf("exit\n");
	if (!shell || !args || !args[1])
		exit_error_cleanup(shell, NULL, shell->exit_status);
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_error_cleanup(shell, NULL, 2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit_error_cleanup(shell, NULL, ft_atoi(args[1]));
	return (0);
}
