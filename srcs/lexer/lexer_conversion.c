#include "../../includes/minishell.h"

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
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
