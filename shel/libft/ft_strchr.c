/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 18:48:31 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/01 22:54:02 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*s1;
	int		i;

	s1 = (char *)str;
	i = 0;
	while (s1[i] != 0)
	{
		if (s1[i] == ch)
		{
			return (&s1[i]);
		}
		i++;
	}
	if (s1[i] == '\0' && ch == '\0')
		return (&s1[i]);
	return (NULL);
}
