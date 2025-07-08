/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:30:52 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/09 20:49:40 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = ((unsigned char *)s1);
	p2 = ((unsigned char *)s2);
	if (n == 0)
		return (0);
	while (*p1 == *p2 && n - 1 > 0)
	{
		p1++;
		p2++;
		n--;
	}
	return ((int)*p1 - *p2);
}

/* int	main(void)
{
	unsigned char	p1[]="ho";
	unsigned char	p2[]="hola";
	
	printf("%d\n", ft_memcmp(p1, p2, 4));
	return (0);
} */