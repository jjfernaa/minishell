#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "env") == 0 || ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	execute_command(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (execute_builtin(args, shell));
	else
		return (execute_external(args, shell));
}
