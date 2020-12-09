/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frstsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:55:59 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/28 15:56:03 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			cnt(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	char		*getbefore(char *s, char c)
{
	int		i;
	int		j;
	char	*k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	k = malloc(sizeof(char) * i + 1);
	while (s[j] && j < i)
	{
		k[j] = s[j];
		j++;
	}
	k[i] = 0;
	return (k);
}

static	int			cpos(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static	char		*getafter(char *s, char c)
{
	int		i;
	int		j;
	int		f;
	char	*k;

	f = 0;
	i = cpos(s, c);
	j = ft_strlen(s);
	k = malloc(sizeof(char) * (j - i));
	i++;
	while (s[i])
	{
		k[f] = s[i];
		f++;
		i++;
	}
	k[f] = 0;
	return (k);
}

char				**ft_frstsplit(char *s, char c)
{
	char	**res;

	if (!(cnt(s, c)))
		return (NULL);
	if (!(res = malloc(sizeof(char *) * 2)))
		return (NULL);
	res[0] = getbefore(s, c);
	res[1] = getafter(s, c);
	return (res);
}
