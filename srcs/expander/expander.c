#include "minishell.h"

static void	append_exit_status(char **result, int exit_status, int *i)
{
	char	*exit_status_str;
	char	*new_str;

	exit_status_str = ft_itoa(exit_status);
	if (!exit_status_str)
		return ;
	new_str = ft_strjoin(*result, exit_status_str);
	free(exit_status_str);
	if (!new_str)
		return ;
	free(*result);
	*result = new_str;
	*i += 2;
}

static void	append_char(char **result, char c)
{
	char	*new_str;
	size_t	len;

	if (!result || !*result)
		return ;
	len = ft_strlen(*result);
	new_str = malloc(len + 2);
	if (!new_str)
		return ;
	ft_memcpy(new_str, *result, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(*result);
	*result = new_str;
}

static void	append_env_var(char **result, const char *str, t_env *env, int *i)
{
	int		len;
	char	*new_string;
	char	*var_name;
	char	*value;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return ;
	value = get_env_value_list(env, var_name);
	free(var_name);
	if (!value)
	{
		*i += len + 1;
		return ;
	}
	new_string = ft_strjoin(*result, value);
	if (!new_string)
		return ;
	free(*result);
	*result = new_string;
	*i += len + 1;
}

static char	*expand_string(const char *str, t_env *env, int exit_status)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				append_exit_status(&result, exit_status, &i);
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				append_env_var(&result, str + i + 1, env, &i);
			else
				append_char(&result, str[i++]);
		}
		else
			append_char(&result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	expand_var(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	char	*old_value;
	char	*new_value;

	current = tokens;
	if (!current)
		return ;
	while (current)
	{
		if (current->type == T_WORD && current->quote_type != SINGLE_QUOTE)
		{
			old_value = current->value;
			new_value = expand_string(
					current->value,
					shell->env,
					shell->exit_status);
			if (new_value)
			{
				current->value = new_value;
				free(old_value);
			}
		}
		current = current->next;
	}
}
