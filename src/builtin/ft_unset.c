/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:41:14 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/25 22:41:20 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		in2(t_config *cnf, t_env *tenv, t_env *tenv2, int i)
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

void			remove_env(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;
	t_env	*tenv2;

	i = 1;
	tenv = cnf->senvl;
	tenv2 = cnf->senvl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->value, argv)))
		{
			if (in2(cnf, tenv, tenv2, i))
				break ;
		}
		tenv = tenv->next;
		i++;
	}
}

void			freed22(t_env *tenv, t_env *tenv2, t_config *cnf)
{
	tenv2 = tenv2->next;
	cnf->envl = tenv2;
	free(tenv->key);
	free(tenv->value);
	free(tenv);
}

int				env_exist(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;

	i = 0;
	tenv = cnf->envl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->value, argv)))
			return (1);
		tenv = tenv->next;
	}
	return (0);
}

int				ft_unset(char **argv, t_config *cnf)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (env_exist(argv[i], cnf))
		{
			remove_env(argv[i], cnf);
			remove_env2(argv[i], cnf);
		}
		i++;
	}
	return (errno);
}
