/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 01:04:16 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/27 01:04:18 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		compare_str(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int		ft_echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (argv[1])
	{
		flag = compare_str(argv[1], "-n");
		if (flag == 0)
			i = 1;
		while (argv[i])
		{
			i++;
			ft_putstr_fd(argv[i], 1);
		}
	}
	else
		write(1, "\n", 1);
	if (flag)
		write(1, "\n", 1);
	return (errno);
}

int		main(int argc, char **argv)
{
	return (ft_echo(argv));
}
