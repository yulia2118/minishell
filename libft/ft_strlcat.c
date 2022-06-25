/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 20:13:55 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/27 00:43:52 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t d;
	size_t s;
	size_t res;

	if (!size)
		return (ft_strlen(src));
	d = ft_strlen(dest);
	if (d <= size)
		res = d;
	else
		res = size;
	s = 0;
	while (src[s])
	{
		if (d < size - 1)
			dest[d++] = src[s];
		res++;
		s++;
	}
	dest[d] = '\0';
	return (res);
}
