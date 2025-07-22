#include "../../includes/minishell.h"

char	*check_direct_path(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

static char	*build_full_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	return (full_path);
}

char	*search_in_dirs(char **dirs, char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = build_full_path(dirs[i], command);
		if (!full_path)
		{
			free_array(dirs);
			return (NULL);
		}
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}
