/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:07:07 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/02 22:58:33 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	f;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen((char *)s1);
	f = ft_strlen((char *)s2);
	if (!(new = malloc(sizeof(*new) * (f + i + 1))))
		return (NULL);
	i = 0;
	f = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[f] != '\0')
	{
		new[i + f] = s2[f];
		f++;
	}
	new[i + f] = '\0';
	return (new);
}
