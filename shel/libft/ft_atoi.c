/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:15:53 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/05 21:33:23 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_over(char *s1, int pos_neg)
{
	int over;
	int chek;
	int i;

	i = 0;
	over = 0;
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		chek = over;
		over = over * 10 + (s1[i] - '0');
		if (i > 17)
		{
			if (over > chek && pos_neg == -1 && (s1[i] - '0') > 8)
				return (0);
			if (over > chek && pos_neg == 1 && (s1[i] - '0') > 7)
				return (-1);
		}
		i++;
	}
	return (over);
}

int				ft_atoi(const char *str)
{
	long long int	res;
	int				pos_neg;

	res = 0;
	pos_neg = 1;
	while (*str == '\t' || *str == ' ' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pos_neg = -1;
		str++;
	}
	res = ft_over((char *)str, pos_neg);
	return (res * pos_neg);
}
