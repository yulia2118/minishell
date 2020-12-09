/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 23:46:34 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/30 22:04:37 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		freemem(char **arr)
{
	size_t	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c)
			size++;
		while (s[i + 1] && s[i] != c)
			i++;
		i++;
	}
	return (size);
}

static size_t	countchar(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_split(char const *s, char c)
{
	char		**array;
	size_t		i;
	size_t		start;

	if (!s || !(array = (char**)malloc(sizeof(char*) * (countwords(s, c) + 1))))
		return (NULL);
	i = 0;
	start = 0;
	while (i < countwords(s, c))
	{
		while (s[start] == c)
			start++;
		if (!(array[i] = ft_substr(s, start, countchar(&s[start], c))))
		{
			freemem(array);
			return (NULL);
		}
		while (s[start] && s[start] != c)
			start++;
		i++;
	}
	array[i] = NULL;
	return (array);
}
