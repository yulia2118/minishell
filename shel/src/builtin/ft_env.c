/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:25 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/18 15:22:32 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **environ)
{
	while (*environ)
	{
		write(1, *environ, ft_strlen(*environ));
		write(1, "\n", 1);
		environ++;
	}
	return (errno);
}
