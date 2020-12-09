/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 21:16:13 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/28 15:13:41 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len && *big)
	{
		i = ft_strlen(little);
		while (*big && i <= len--)
			if (!(ft_strncmp(big++, little, i)))
				return ((char *)--big);
	}
	return (NULL);
}
