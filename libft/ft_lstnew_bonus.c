/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:00 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/18 21:23:46 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/* 
int	main(void)
{
	char	*content;
	t_list	*node;

	content = "Hello, Malaga 42";
	node = ft_lstnew(content);
	printf("%s\n", (char *)node->content);
	free(node);
	return (0);
} */