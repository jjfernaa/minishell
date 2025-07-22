#include "../../includes/minishell.h"

char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	key_len;

	if (!key || !envp)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& envp[i][key_len] == '=')
		{
			return (envp[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}

static char	*replace_char(char *str, char old, char new)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == old)
			str[i] = new;
		i++;
	}
	return (str);
}

char	*find_executable(char *command, char **envp)
{
	char	*path_env;
	char	*path_copy;
	char	**dirs;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (check_direct_path(command));
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	replace_char(path_copy, ':', ' ');
	dirs = ft_split(path_copy);
	free(path_copy);
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, command));
}
