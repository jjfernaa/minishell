#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

void	free_array(char **array);
int		ft_strcmp(const char *s1, const char *s2);
void	print_cmd_not_found(const char *cmd);
void	sort_string_array(char **array);

#endif