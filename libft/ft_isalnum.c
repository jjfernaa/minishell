/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:04:55 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/09 18:35:23 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

/* int	main(void)
{
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('0'));
	printf("%d\n", ft_isalnum('Z'));
	printf("%d\n", ft_isalnum(':'));
	return (0);
} */
