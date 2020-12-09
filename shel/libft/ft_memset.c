/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:48:34 by wsallei           #+#    #+#             */
/*   Updated: 2020/04/29 19:06:47 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *destination, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = destination;
	i = 0;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (destination);
}
