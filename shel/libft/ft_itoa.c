/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:36:17 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/10 22:04:39 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_sizenum(int n)
{
	long int	num;
	int			cnum;

	cnum = 0;
	num = n;
	if (n == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		cnum++;
	}
	while (n != 0)
	{
		n /= 10;
		cnum++;
	}
	return (cnum);
}

char			*ft_itoa(int n)
{
	int			size;
	long int	num;
	char		*res;

	size = ft_sizenum(n);
	num = n;
	if (!(res = malloc(sizeof(*res) * (size + 1))))
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		res[0] = '-';
	}
	res[size] = '\0';
	if (num == 0)
		res[size - 1] = '0';
	while (size > 0 && num != 0)
	{
		res[size - 1] = (num % 10) + '0';
		num /= 10;
		size--;
	}
	return (res);
}
