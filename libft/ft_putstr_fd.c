/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:47:28 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/16 19:28:07 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
}

/* int	main(void)
{
	char *str= "Hola Malaga 42";
	
	ft_putstr_fd(str, 1);
	write (1, "\n", 1);
	return (0);
} */
