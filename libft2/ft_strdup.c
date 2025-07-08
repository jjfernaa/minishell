/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:26:21 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/10 17:52:26 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * size +1);
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, src, size);
	dest[size] = '\0';
	return (dest);
}
/* 
int	main(void)
{
	const char	*origin;
	char		*dup;

	origin = "Malaga 42";
	dup = ft_strdup(origin);
	if (dup == NULL)
	{
		printf("Error: No se pudo duplicar la cadena.\n");
		return (1);
	}
	printf("Cadena original: %s\n", origin);
	printf("Cadena duplicada: %s\n", dup);
	free(dup);
	return (0);
} */
