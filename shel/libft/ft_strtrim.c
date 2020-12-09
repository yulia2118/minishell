/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:59:36 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/03 00:04:56 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_sep(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int				f;
	int				s;
	unsigned int	siz;
	char			*rez;

	s = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[s] && ft_sep((char)s1[s], set))
		s++;
	if ((f = ft_strlen(s1) - 1) != -1)
	{
		while (f >= 0 && ft_sep((char)s1[f], set))
			f--;
	}
	if (&s1[s] == &s1[f])
		siz = 2;
	else
		siz = &s1[f] - &s1[s] + 2;
	if (!(rez = malloc(sizeof(char) * siz)))
		return (NULL);
	ft_strlcpy(rez, &s1[s], siz);
	return (rez);
}
