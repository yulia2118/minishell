/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecpu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:43:18 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 21:44:04 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int			ini2(t_config *cnf, t_env *tenv, t_env *tenv2, int i)
{
	int		j;
	int		remove;

	j = 1;
	remove = siseenv(cnf);
	if ((i != 1 && i != remove) || i == 1)
	{
		freed(tenv, tenv2, i, j);
		return (1);
	}
	else if (i == 1)
	{
		freed2(tenv, tenv2, cnf);
		return (1);
	}
	else if (i == remove)
	{
		freed3(tenv, tenv2, j, remove);
		return (1);
	}
	return (0);
}

void				re_env2(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;
	t_env	*tenv2;

	i = 1;
	tenv = cnf->envl;
	tenv2 = cnf->envl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->key, argv)))
		{
			if (ini2(cnf, tenv, tenv2, i))
				break ;
		}
		tenv = tenv->next;
		i++;
	}
}

static	int			in1(t_config *cnf, t_env *tenv, t_env *tenv2, int i)
{
	int		j;
	int		remove;

	j = 1;
	remove = siseenv(cnf);
	if (i != 1 && i != remove)
	{
		freed(tenv, tenv2, i, j);
		return (1);
	}
	else if (i == 1)
	{
		freed22(tenv, tenv2, cnf);
		return (1);
	}
	else if (i == remove)
	{
		freed3(tenv, tenv2, j, remove);
		return (1);
	}
	return (0);
}

void				remove_env2(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;
	t_env	*tenv2;

	i = 1;
	tenv = cnf->envl;
	tenv2 = cnf->envl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->value, argv)))
		{
			if (in1(cnf, tenv, tenv2, i))
				break ;
		}
		tenv = tenv->next;
		i++;
	}
}
