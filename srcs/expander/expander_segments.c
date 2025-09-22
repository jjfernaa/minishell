#include "../../includes/minishell.h"

static char	*expand_single_segment(t_token_segment *segment, t_env *env, int exit_status)
{
	if (segment->quote_type == SINGLE_QUOTE)
		return (ft_strdup(segment->content));
	else if (segment->quote_type == DOUBLE_QUOTE || segment->quote_type == NO_QUOTE)
		return (expand_string(segment->content, env, exit_status));
	else
		return (ft_strdup(segment->content));
}

static char	*join_expanded_segments(char *result, char *expanded_segment)
{
	char	*temp;

	temp = ft_strjoin(result, expanded_segment);
	free(result);
	free(expanded_segment);
	return (temp);
}

char	*expand_token_with_segments(t_token *token, t_env *env, int exit_status)
{
	char			*result;
	char			*expanded_segment;
	t_token_segment	*current;

	if (!token->segments)
		return (expand_string(token->value, env, exit_status));
	result = ft_strdup("");
	current = token->segments;
	while (current)
	{
		expanded_segment = expand_single_segment(current, env, exit_status);
		result = join_expanded_segments(result, expanded_segment);
		current = current->next;
	}
	return (result);
}

void	expand_var(t_shell *shell)
{
	t_token	*current;
	char	*old_value;
	char	*new_value;

	current = shell->tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			old_value = current->value;
			new_value = expand_token_with_segments(current, shell->env, shell->exit_status);
			if (new_value && new_value != old_value)
			{
				current->value = new_value;
				free(old_value);
			}
		}
		current = current->next;
	}
}
