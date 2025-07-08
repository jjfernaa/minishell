/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:42:02 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/17 03:53:45 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* static char ft_to_lower(unsigned int i, char c)
{
	(void)i;
	return (char)ft_tolower(c);
}
int	main(void)
{
	char	*origin = "HOLA MALAGA";
	char	*result = ft_strmapi(origin, ft_to_lower);
	
	printf("%s\n", result);
	free (result);
	return (0);
} */