#include "lexer.h"

static t_token_segment	*new_segment(const char *value, t_quote_type quote_type)
{
	t_token_segment	*segment;
	
	segment = malloc(sizeof(segment));
	if (!segment)
		return (NULL);
	if (value)
	{
		segment->text = ft_strdup(value);
		if (!segment->text)
		{
			free(segment);
			return (NULL);
		}
	}
	else
		segment->text = NULL;
	segment->quote_type = quote_type;
	segment->next = NULL;
	return (segment);
}

static void	segment_add_back(t_token_segment **list, t_token_segment *new)
{
	t_token_segment	*tmp;

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

int	*add_segment_to_token(t_token *token, const char *value, t_quote_type quote_type)
{
	t_token_segment	*new;

	new = new_segment(value, quote_type);
	if (!new)
		return (0);
	segment_add_back(&token->segments, new);
	return (1);
}

void	free_segments(t_token_segment *segments)
{
	t_token_segment	*current;
	t_token_segment	*next;

	current = segments;
	while (current)
	{
		next = current->next;
		if (current->text)
			free(current->text);
		free(current);
		current = next;
	}
}
