/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:06:25 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/09 13:06:27 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				chckqte(char *line, int i, t_tmp *tmp, int type)
{
	if ((line[i] == '\'' && type == 0 && tmp->st == 0))
	{
		tmp->st = 2;
		type = 1;
	}
	else if ((line[i] == '\"' && type == 0 && tmp->st == 0))
		type = 2;
	else if ((line[i] == '\'' && type == 1))
	{
		tmp->st = 0;
		type = 0;
	}
	else if ((line[i] == '\"' && type == 2 && tmp->st == 0))
		type = 0;
	return (type);
}

void			ccn(char *line, t_tmp *tmp, int i, int type)
{
	if (line[i] == '\\' && line[i + 1]
		&& type == 0 && !ft_isalnum(line[i + 1]) && tmp->st == 0)
		tmp->st = 1;
	else if (line[i] == '\\' && line[i + 1]
		&& type == 0 && ft_isalnum(line[i + 1]) && tmp->st == 0)
		tmp->st = 0;
	else if (line[i] == '\\' && line[i + 1]
		&& type == 2 && !ft_isalnum(line[i + 1]) && tmp->st == 0)
		tmp->st = 1;
	else if (line[i] == '\\' && line[i + 1]
		&& type == 2 && ft_isalnum(line[i + 1]))
		tmp->st = 0;
	else if (line[i] == '\\' && !line[i + 1])
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && type == 0)
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && type == 2)
		tmp->st = 0;
	else if (line[i] != '\\' && tmp->st == 1)
		tmp->st = 0;
}

int				close_quote(char *line)
{
	int		i;
	int		type;
	t_tmp	tmp;

	type = 0;
	i = 0;
	tmp.st = 0;
	while (line[i])
	{
		type = chckqte(line, i, &tmp, type);
		ccn(line, &tmp, i, type);
		i++;
	}
	return (type);
}
