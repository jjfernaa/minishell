/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:38:38 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/15 19:04:14 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	f;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		f = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[f - 1] && ft_strchr(set, s1[f - 1]) && f > i)
			f--;
		str = (char *)malloc(sizeof(char) * (f - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], f - i +1);
	}
	return (str);
}

/* int	main(void)
{
	char	s1[]="cccHoladdc";
	char	set[]="cd";
	char 	*result;

	result = ft_strtrim(s1, set);
	if (result)
	{
		printf ("%s\n", result);
		free (result);
	}
	return (0);
} */