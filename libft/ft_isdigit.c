/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:02:34 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/17 21:06:27 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/* int	main(void)
{
	int	a;
	int	b;

	a = 'a';
	b = '4';
	printf("%d\n", ft_isdigit(a));
	printf("%d\n", ft_isdigit(b));
	return (0);
} */