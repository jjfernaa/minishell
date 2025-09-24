/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:26:06 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:26:07 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_args(t_token *tokens)
{
	char	**args;
	t_token	*tmp;
	int		count;
	int		i;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
			count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && i < count)
	{
		if (tokens->type == T_WORD)
			args[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}
