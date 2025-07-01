/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:38:17 by juan-jof          #+#    #+#             */
/*   Updated: 2025/07/02 01:15:11 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_command(char *input)
{
	if (strcmp(input, "pwd") == 0)
	{
		builtin_pwd();
	}
	else
	{
		printf("Has escrito: '%s'\n", input);
	}
}
