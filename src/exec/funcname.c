/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:48:55 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 00:39:48 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static	int			ccg(t_tok *pnt, t_tmp *tmp, char *ret, t_config *cnf)
{
	if (pnt->func[tmp->i + 1] && pnt->func[tmp->i + 1] == '?')
	{
		gtc(tmp, cnf, ret);
	}
	else
	{
		tmp->i++;
		ptenv(pnt->func, cnf->envl, tmp, ret);
		tmp->j--;
		if (pnt->func[tmp->i] == '\0')
			return (tmp->i - 1);
		tmp->i--;
	}
	return (tmp->i);
}

static	int			condi(t_tok *pnt, t_tmp *tmp, int eq)
{
	if ((pnt->func[tmp->i] == '\'' || pnt->func[tmp->i] == '\"')
		&& eq == 0 && tmp->st == 0)
		tmp->j--;
	if (pnt->func[tmp->i] == '\'' && eq == 1)
		tmp->j--;
	if (pnt->func[tmp->i] == '\"' && eq == 2 && tmp->st == 0)
		tmp->j--;
	return (tmp->j);
}

static	void		ii(t_tmp *tmp)
{
	tmp->st = 0;
	tmp->i = 0;
	tmp->j = 0;
	tmp->eq = 0;
}

char				*namefunc(t_config *cnf, t_tok *pnt, int len)
{
	t_env	*env;
	char	*ret;
	t_tmp	tmp;

	env = cnf->envl;
	ii(&tmp);
	ret = malloc(sizeof(char) * len + 1);
	while (pnt->func[tmp.i] && tmp.j < len)
	{
		tmp.eq = checkqq(pnt->func, tmp.i, tmp.eq, &tmp);
		if ((pnt->func[tmp.i] != '$') || (pnt->func[tmp.i] == '$' &&
			tmp.st == 1) || tmp.eq == 1)
			ret[tmp.j] = pnt->func[tmp.i];
		if ((pnt->func[tmp.i] == '$' && tmp.eq != 1 && tmp.st == 0))
			tmp.i = ccg(pnt, &tmp, ret, cnf);
		tmp.j = condi(pnt, &tmp, tmp.eq);
		checkslh(pnt->func, tmp.i, &tmp);
		tmp.j++;
		tmp.i++;
	}
	ret[tmp.j] = 0;
	return (ret);
}
