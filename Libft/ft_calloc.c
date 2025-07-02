/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:05:38 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/10 13:50:47 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	array = (void *)malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (count * size));
	return (array);
}

/* int main()
{
    size_t	count; 
    size_t	size;
	int		*arr;
	
	count = 15;
	size = sizeof(int);
    arr = (int *)malloc(count * size);
    if (arr == NULL)
    {
        printf("Error\n");
        return 1;
    }

    size_t i = 0;
    while (i < count)
    {
        printf("arr[%zu] = %d\n", i,  arr[i]);
        i++;
    }

    free(arr);
    return 0;
}
 */