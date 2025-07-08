/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:41:16 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/15 23:40:18 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(int num)
{
	int	count;

	count = 0;
	if (num != 0)
	{
		if (num < 0)
		{
			num = -num;
			count++;
		}
		while (num != 0)
		{
			num = num / 10;
			count++;
		}
	}
	else
		count = 1;
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long int	nbr;

	len = count_c(n);
	nbr = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (nbr)
	{
		str[len] = ((nbr % 10) + '0');
		nbr /= 10;
		len--;
	}
	return (str);
}
/* 
int	main(void)
{
	int		n;
	char	*str;
	
	n = 7;
	str = ft_itoa(n);
	printf("%s\n", str);
	free(str);
	return (0);
} */