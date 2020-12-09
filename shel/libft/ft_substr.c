/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:09:12 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/02 22:06:32 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	f;

	if (!s)
		return (NULL);
	i = 0;
	f = 0;
	while (i < start && s[i] != '\0')
		i++;
	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	while ((f < len) && s[i + f] != '\0')
	{
		res[f] = s[i + f];
		f++;
	}
	res[f] = '\0';
	return (res);
}
