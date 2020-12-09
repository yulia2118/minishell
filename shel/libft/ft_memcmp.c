/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 16:00:59 by wsallei           #+#    #+#             */
/*   Updated: 2020/04/30 16:37:20 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t				i;
	unsigned const char	*tmp1;
	unsigned const char	*tmp2;

	i = 0;
	tmp1 = arr1;
	tmp2 = arr2;
	while (i < n)
	{
		if (tmp1[i] == tmp2[i])
			i++;
		else
			return (tmp1[i] - tmp2[i]);
	}
	return (0);
}
