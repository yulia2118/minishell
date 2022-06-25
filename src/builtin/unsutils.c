/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:59:32 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 19:59:34 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		siseenv(t_config *cnf)
{
	int		i;
	t_env	*tenv;

	i = 0;
	tenv = cnf->senvl;
	while (tenv)
	{
		tenv = tenv->next;
		i++;
	}
	return (i);
}

void	freed(t_env *tenv, t_env *tenv2, int i, int j)
{
	while (tenv2 && j < i - 1)
	{
		tenv2 = tenv2->next;
		j++;
	}
	tenv2->next = tenv->next;
	free(tenv->key);
	free(tenv->value);
	free(tenv);
}

void	freed2(t_env *tenv, t_env *tenv2, t_config *cnf)
{
	tenv2 = tenv2->next;
	cnf->senvl = tenv2;
	free(tenv->key);
	free(tenv->value);
	free(tenv);
}

void	freed3(t_env *tenv, t_env *tenv2, int j, int remove)
{
	while (tenv2 && j < remove - 1)
	{
		tenv2 = tenv2->next;
		j++;
	}
	tenv2->next = NULL;
	free(tenv->key);
	free(tenv->value);
	free(tenv);
}

int		siseen(t_config *cnf)
{
	int		i;
	t_env	*tenv;

	i = 0;
	tenv = cnf->envl;
	while (tenv)
	{
		tenv = tenv->next;
		i++;
	}
	return (i);
}
