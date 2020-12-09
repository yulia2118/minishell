/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:56:59 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/06 14:42:49 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t f;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		f = 0;
		if (big[i] == little[f])
		{
			while ((big[i + f] == little[f]) && (little[f] != '\0') &&
				(i + f < len))
				f++;
			if (little[f] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
