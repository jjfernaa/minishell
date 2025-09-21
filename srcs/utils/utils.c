#include "utils.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_cmd_not_found(const char *cmd)
{
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 21);
}

void	sort_string_array(char **array)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	if (!array)
		return ;
	size = 0;
	while (array[size])
		size++;
	i = -1;
	while (++i < size -1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
	}
}
