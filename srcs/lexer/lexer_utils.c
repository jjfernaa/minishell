/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:26:26 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:26:27 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*new_token(t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = NULL;
	token->quote_type = NO_QUOTE;
	token->segments = NULL;
	token->next = NULL;
	return (token);
}

static void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*add_token(t_token **list, t_token_type type)
{
	t_token	*new;

	new = new_token(type);
	if (!new)
		return (NULL);
	token_add_back(list, new);
	return (new);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->segments)
			free_segments(tmp->segments);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
