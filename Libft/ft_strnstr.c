/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:28:49 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/16 02:40:28 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *origin, const char *search, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!origin && !len)
		return (0);
	if (search[0] == '\0' || search == origin)
		return ((char *)origin);
	while (origin[i] != '\0')
	{
		j = 0;
		while (origin[i + j] == search[j] && (i + j) < len)
		{
			if (origin[i + j] == '\0' && search[j] == '\0')
				return ((char *)&origin[i]);
			j++;
		}
		if (search[j] == '\0')
			return ((char *)(origin + i));
		i++;
	}
	return (0);
}

/* 
int	main(void)
{
	char	h[]="hola mundo";
	char	n[]="hol";
	
	printf("%s\n", ft_strnstr(h, n, 6));
	printf("%s\n", ft_strnstr(h, n, 2));
	
	return (0);

} */