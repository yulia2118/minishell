/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slhs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:55:03 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 16:55:05 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int			contcheck(char *line, int i, t_tmp *tmp, int count)
{
	if (line[i] == '\\' && line[i + 1] && tmp->eq == 2
		&& ft_isalnum(line[i + 1]))
		tmp->st = 0;
	else if (line[i] == '\\' && !line[i + 1])
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && tmp->eq == 0)
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && tmp->eq == 2)
		tmp->st = 0;
	else if (line[i] != '\\' && tmp->st == 1)
		tmp->st = 0;
	return (count);
}

int					checslash(char *line, int i, t_tmp *tmp, int count)
{
	if (line[i] == '\\' && line[i + 1] && tmp->eq == 0
		&& !ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 1;
		count--;
	}
	else if (line[i] == '\\' && line[i + 1] && tmp->eq == 0
		&& ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 0;
		count--;
	}
	else if (line[i] == '\\' && line[i + 1] && tmp->eq == 2
		&& !ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 1;
		count--;
	}
	else
		count = contcheck(line, i, tmp, count);
	return (count);
}

int					checkqq(char *line, int i, int eq, t_tmp *tmp)
{
	if ((line[i] == '\'' && eq == 0 && tmp->st == 0))
	{
		tmp->st = 2;
		eq = 1;
	}
	else if ((line[i] == '\"' && eq == 0 && tmp->st == 0))
		eq = 2;
	else if ((line[i] == '\'' && eq == 1))
	{
		tmp->st = 0;
		eq = 0;
	}
	else if ((line[i] == '\"' && eq == 2 && tmp->st == 0))
		eq = 0;
	return (eq);
}

static	void		csslh(char *line, int i, t_tmp *tmp)
{
	if (line[i] == '\\' && line[i + 1] && tmp->eq == 2
		&& ft_isalnum(line[i + 1]))
		tmp->st = 0;
	else if (line[i] == '\\' && !line[i + 1])
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && tmp->eq == 0)
		tmp->st = 0;
	else if (line[i] == '\\' && tmp->st == 1 && tmp->eq == 2)
		tmp->st = 0;
	else if (line[i] != '\\' && tmp->st == 1)
		tmp->st = 0;
}

void				checkslh(char *line, int i, t_tmp *tmp)
{
	if (line[i] == '\\' && line[i + 1] && tmp->eq == 0
		&& !ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 1;
		tmp->j--;
	}
	else if (line[i] == '\\' && line[i + 1] && tmp->eq == 0
		&& ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 0;
		tmp->j--;
	}
	else if (line[i] == '\\' && line[i + 1] && tmp->eq == 2
		&& !ft_isalnum(line[i + 1]) && tmp->st == 0)
	{
		tmp->st = 1;
		tmp->j--;
	}
	else
		csslh(line, i, tmp);
}
