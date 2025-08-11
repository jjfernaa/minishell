#include "../../includes/minishell.h"

int	count_commands(t_cmd *cmds)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmds;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	handle_pipe_error(int **pipes, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	if (pipes &&pipes[created_count])
		free(pipes[created_count]);
	free(pipes);
}
