/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:40:28 by juan-jof          #+#    #+#             */
/*   Updated: 2025/07/02 02:25:32 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static size_t	count_words(char const *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_separator(s[i]))
			i++;
		if (s[i] && !is_separator(s[i]))
		{
			count++;
			while (s[i] && !is_separator(s[i]))
				i++;
		}
	}
	return (count);
}

static char	*extract_word(char const *s, size_t *start)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[*start] && is_separator(s[*start]))
		(*start)++;
	while (s[*start + len] && !is_separator(s[*start + len]))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + *start, len + 1);
	*start += len;
	return (word);
}

static void	free_array(char **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s)
{
	char	**result;
	size_t	word_count;
	size_t	i;
	size_t	start;

	if (!s)
		return (NULL);
	word_count = count_words(s);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < word_count)
	{
		result[i] = extract_word(s, &start);
		if (!result[i])
		{
			free_array(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
