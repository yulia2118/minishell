/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:35:40 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/09 20:35:42 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_parsnbr(int n, int fd)
{
	if (n / 10 != 0)
		ft_parsnbr((n / 10), fd);
	ft_putchar_fd((-(n % 10) + '0'), fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	else
		n = -n;
	ft_parsnbr(n, fd);
}
