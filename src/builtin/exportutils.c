/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:07:32 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 20:07:33 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		ini(t_config *cnf, t_env *tenv, t_env *tenv2, int i)
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

static	void	re_env(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;
	t_env	*tenv2;

	i = 1;
	tenv = cnf->senvl;
	tenv2 = cnf->senvl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->key, argv)))
		{
			if (ini(cnf, tenv, tenv2, i))
				break ;
		}
		tenv = tenv->next;
		i++;
	}
}

static	int		env_exi(char *argv, t_config *cnf)
{
	int		i;
	t_env	*tenv;

	i = 0;
	tenv = cnf->envl;
	while (tenv)
	{
		if (!(ft_strcmp(tenv->key, argv)))
			return (1);
		tenv = tenv->next;
	}
	return (0);
}

void			preexp(char **key_value, t_config *cnf)
{
	if (key_value && key_value[0] && key_value[1])
	{
		if (env_exi(key_value[0], cnf))
		{
			re_env(key_value[0], cnf);
			re_env2(key_value[0], cnf);
		}
	}
}

void			postex(t_list *env_list, t_config *cnf)
{
	char	**env;

	env = list_to_array(env_list);
	freeenv(cnf->senvl);
	envtolist(cnf, env, 1);
	tf(env);
	freelistenv(env_list);
}
