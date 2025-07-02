/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:59:52 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/17 21:06:36 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/* int	main(void)
{
	int	a;
	int b;

	a = 'a';
	b = '0';

	printf("%d\n", ft_isalpha(a));
	printf("%d\n", ft_isalpha(b));
	return (0);
} */