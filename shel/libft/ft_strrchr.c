/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 20:25:50 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/01 22:56:15 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s1;
	char	*s2;
	int		i;

	s2 = NULL;
	s1 = (char *)str;
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == ch)
			s2 = &s1[i];
		i++;
	}
	if (s1[i] == '\0' && ch == '\0')
		return (&s1[i]);
	return (s2);
}
