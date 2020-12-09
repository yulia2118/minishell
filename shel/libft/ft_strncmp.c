/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 21:22:48 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/28 14:20:12 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char		*a;
	unsigned char		*b;
	size_t				i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while ((a[i] || b[i]) && (i < n))
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}
