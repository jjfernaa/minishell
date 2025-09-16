#include "../../includes/minishell.h"

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
