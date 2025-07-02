/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:45:10 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/17 03:53:21 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
/* 
static void	ft_upletter(unsigned int i, char *c)
{
	if (i % 2 != 0 && ft_isalpha(*c))
	*c = ft_toupper(*c);
}
int	main(void)
{
	char	str[]= "abcdefghijklmnñopqrstuvwxyz";
	
	ft_striteri(str, ft_upletter);
	printf("%s\n", str);
	return (0);
} */