/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:27:08 by wsallei           #+#    #+#             */
/*   Updated: 2020/04/29 22:44:59 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char		*tmp1;
	unsigned char		*tmp2;
	size_t				i;

	i = 0;
	tmp1 = (unsigned char*)destination;
	tmp2 = (unsigned char*)source;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		if (tmp2[i] == (unsigned char)c)
			return ((void *)&tmp1[i + 1]);
		i++;
	}
	return (NULL);
}
