#include "lexer.h"

/* int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static t_token	*new_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->quote_type = NO_QUOTE;
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

t_token	*add_token(t_token **list, t_token_type type, const char *value)
{
	t_token	*new;

	new = new_token(type, value);
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
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
} */
#include "lexer.h"

int	is_symbol(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

static t_token	*new_token(t_token_type type, const char *value)
{
    t_token	*token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    token->quote_type = NO_QUOTE;
    token->segments = NULL;  // ✅ NUEVO: Inicializar segments
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

t_token	*add_token(t_token **list, t_token_type type, const char *value)
{
    t_token	*new;

    new = new_token(type, value);
    if (!new)
        return (NULL);
    token_add_back(list, new);
    return (new);
}

static void	free_segments(t_token_segment *segments)
{
    t_token_segment	*current;
    t_token_segment	*next;

    current = segments;
    while (current)
    {
        next = current->next;
        if (current->content)
            free(current->content);
        free(current);
        current = next;
    }
}

void	free_tokens(t_token *tokens)
{
    t_token	*tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        if (tmp->value)
            free(tmp->value);
        free_segments(tmp->segments);  // ✅ NUEVO: Liberar segments
        free(tmp);
    }
}
