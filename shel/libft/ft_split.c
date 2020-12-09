/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:57:36 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/06 11:44:42 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		**ft_delmem(char **res, size_t f)
{
	while (f)
	{
		free(res[f]);
		f--;
	}
	free(res);
	return (NULL);
}

static	int			ft_sizewrd(char *s, char c, int i)
{
	int count;

	count = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static	int			ft_cword(char *s, char c)
{
	size_t	i;
	int		count;
	int		wrd;

	count = 0;
	i = 0;
	wrd = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			wrd = 0;
		if (wrd == 0 && s[i] != c)
		{
			wrd = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static	char		**ft_crtwrd(char **res, char *s, char c)
{
	size_t i;
	size_t f;
	size_t g;

	i = 0;
	f = 0;
	g = 0;
	while (s[i] != '\0')
	{
		g = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		if (!(res[f] = malloc(sizeof(**res) * ft_sizewrd(s, c, i) + 1)))
			return (ft_delmem(res, f));
		while (s[i] != '\0' && s[i] != c)
			res[f][g++] = s[i++];
		res[f][g] = '\0';
		f++;
	}
	res[f] = NULL;
	return (res);
}

char				**ft_split(char const *s, char c)
{
	int		f;
	char	**res;

	if (!s)
		return (NULL);
	f = ft_cword((char *)s, c);
	if (!(res = malloc(sizeof(res) * (f + 1))))
		return (NULL);
	res = ft_crtwrd(res, (char *)s, c);
	return (res);
}
