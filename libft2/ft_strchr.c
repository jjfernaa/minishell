/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:34:28 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/09 18:49:46 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}
/* int	main(void)
{
	char	s[]="probando";
	printf("%s\n", ft_strchr(s, 'b'));
	return (0);
} */
