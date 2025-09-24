#include "minishell.h"

static char	*expand_single_segment(t_token_segment *segment, t_env *env, int exit_status)
{
	if (!segment || !segment->text)
		return (ft_strdup(""));
	if (segment->quote_type == SINGLE_QUOTE)
		return (ft_strdup(segment->text));
	else if (segment->quote_type == DOUBLE_QUOTE || segment->quote_type == NO_QUOTE)
		return (expand_string(segment->text, env, exit_status));
	else
		return (ft_strdup(segment->text));
}

static char	*join_expanded_segments(char *result, char *expanded_segment)
{
	char	*temp;

	if (!result && !expanded_segment)
		return (ft_strdup(""));
	if (!result)
		return (expanded_segment);
	if (!expanded_segment)
		return (result);
	temp = ft_strjoin(result, expanded_segment);
	if (!temp)
		return (NULL);
	free(result);
	free(expanded_segment);
	return (temp);
}

char	*expand_token_with_segments(t_token *token, t_env *env, int exit_status)
{
	char			*result;
	char			*expanded_segment;
	t_token_segment	*current;

	if (!token || !token->segments)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	current = token->segments;
	while (current)
	{
		expanded_segment = expand_single_segment(current, env, exit_status);
		if (!expanded_segment)
		{
			free(result);
			return (NULL);
		}
		result = join_expanded_segments(result, expanded_segment);
		if (!result)
			return (NULL);
		current = current->next;
	}
	return (result);
}

void	expand_var(t_shell *shell)
{
	t_token	*current;
	char	*new_value;

	current = shell->tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			new_value = expand_token_with_segments(current, shell->env, shell->exit_status);
			if (current->value)
				free(current->value);
			if (new_value)
				current->value = new_value;
			else
				current->value = ft_strdup("");
		}
		current = current->next;
	}
}
