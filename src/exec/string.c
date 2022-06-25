/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:17:47 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 00:17:49 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int			initi(t_tmp *tmp, t_arg *arg, t_config *cnf)
{
	int len;

	len = 0;
	tmp->i = 0;
	tmp->j = 0;
	tmp->eq = 0;
	tmp->st = 0;
	len = specstrlen(arg->sarg, cnf);
	return (len);
}

static	void		gtc(t_tmp *tmp, t_config *cnf, char *ret)
{
	char	*ss;
	int		k;

	k = 0;
	ss = ft_itoa(cnf->excode);
	while (ss[k])
	{
		ret[tmp->j] = ss[k];
		tmp->j++;
		k++;
	}
	tmp->j--;
	tmp->i++;
	free(ss);
}

static	int			ccg(t_arg *arg, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (arg->sarg[tmp->i + 1] && arg->sarg[tmp->i + 1] == '?')
	{
		gtc(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(arg->sarg, cnf->envl, tmp, ret);
		tmp->j--;
		if (arg->sarg[tmp->i] == '\0')
			return (tmp->i - 1);
		tmp->i--;
	}
	return (tmp->i);
}

static	int			condiis(t_arg *arg, t_tmp *tmp, int eq)
{
	if ((arg->sarg[tmp->i] == '\'' || arg->sarg[tmp->i] == '\"')
		&& eq == 0 && tmp->st == 0)
		tmp->j--;
	if (arg->sarg[tmp->i] == '\'' && eq == 1)
		tmp->j--;
	if (arg->sarg[tmp->i] == '\"' && eq == 2 && tmp->st == 0)
		tmp->j--;
	return (tmp->j);
}

char				*getstr(t_arg *arg, t_config *cnf)
{
	char	*ret;
	int		len;
	t_tmp	tmp;

	len = initi(&tmp, arg, cnf);
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (arg->sarg[tmp.i])
	{
		tmp.eq = checkqq(arg->sarg, tmp.i, tmp.eq, &tmp);
		if ((arg->sarg[tmp.i] != '$') || (arg->sarg[tmp.i] == '$' &&
			tmp.st == 1) || tmp.eq == 1)
			ret[tmp.j] = arg->sarg[tmp.i];
		if ((arg->sarg[tmp.i] == '$' && tmp.eq != 1 && tmp.st == 0))
			tmp.i = ccg(arg, &tmp, ret, cnf);
		tmp.j = condiis(arg, &tmp, tmp.eq);
		checkslh(arg->sarg, tmp.i, &tmp);
		tmp.j++;
		tmp.i++;
	}
	ret[tmp.j] = 0;
	return (ret);
}
