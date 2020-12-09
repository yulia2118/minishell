/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:05:56 by wsallei           #+#    #+#             */
/*   Updated: 2020/04/30 15:07:05 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_else(unsigned char *tmp, unsigned char *tmp2, size_t n)
{
	while (n > 0)
	{
		tmp[n - 1] = tmp2[n - 1];
		n--;
	}
}

void			*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char		*tmp;
	unsigned char		*tmp2;
	size_t				i;

	i = 0;
	tmp = (unsigned char *)destination;
	tmp2 = (unsigned char *)source;
	if ((n == 0) || (destination == source))
		return (destination);
	if (destination <= source)
	{
		while (i < n)
		{
			tmp[i] = tmp2[i];
			i++;
		}
	}
	else
		ft_else(tmp, tmp2, n);
	return (destination);
}
