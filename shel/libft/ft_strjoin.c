/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 23:40:41 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/26 22:35:52 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*newstr;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(newstr = (char*)malloc(sizeof(char) + (len + 1))))
		return (NULL);
	while (*s1 != '\0')
	{
		newstr[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		newstr[i] = *s2++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
