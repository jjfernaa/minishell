/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:24:01 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/10 21:21:16 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			j;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	j = 1;
	d = ((unsigned char *)dest);
	s = ((unsigned char *)src);
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		j = -1;
		d += n - 1;
		s += n - 1;
	}
	while (i < n)
	{
		*d = *s;
		d += j;
		s += j;
		i++;
	}
	return (dest);
}

/* int	main(void)
{
	char	src[50]="hola malaga";
	char	dest[50]="";
	
	ft_memmove(dest, src, ft_strlen(src) + 1);
	printf("Prueba uno:\n");
	printf("src = %s\ndest = %s\n", src, dest);

	ft_memmove(src + 5, src, ft_strlen(src) + 1);
	printf("Prueba dos:\n");
	printf("src 2 = %s\n", src);

	ft_memmove(src, src + 5, ft_strlen(src + 5) + 1);
	printf("Prueba tres:\n");
	printf("src 3 = %s\n", src);
	return (0);  
} */