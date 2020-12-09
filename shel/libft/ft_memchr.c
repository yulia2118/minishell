/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:08:01 by wsallei           #+#    #+#             */
/*   Updated: 2020/04/30 15:56:26 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*arr2;

	arr2 = (unsigned char *)arr;
	i = 0;
	while (i < n)
	{
		if (arr2[i] == (unsigned char)c)
			return ((void *)&arr2[i]);
		i++;
	}
	return (NULL);
}
