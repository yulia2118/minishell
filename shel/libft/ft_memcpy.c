/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:59:48 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/06 16:38:54 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char		*tmp1;
	unsigned const char	*tmp2;
	size_t				i;

	i = 0;
	tmp1 = (unsigned char*)destination;
	tmp2 = (unsigned char*)source;
	if ((n == 0) || (destination == source))
		return (destination);
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i++;
	}
	return (destination);
}
