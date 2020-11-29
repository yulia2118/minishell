/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:13:44 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/16 14:34:23 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (errno);
}

