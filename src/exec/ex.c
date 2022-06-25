/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:21:57 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/28 20:22:00 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void			cle(char *tm, char *str, t_tmp *tmp, int j)
{
	int c;

	c = 0;
	while (tmp->i < j)
	{
		tm[c] = str[tmp->i];
		tmp->i++;
		c++;
	}
	tm[c] = 0;
}

static	void			envp(t_env *e, char *s, t_tmp *tmp)
{
	int j;

	j = 0;
	while (e && e->value[j])
	{
		s[tmp->j] = e->value[j];
		tmp->j++;
		j++;
	}
}

void					ptenv(char *str, t_env *env, t_tmp *tmp, char *s)
{
	t_env	*e;
	int		j;
	char	*tm;

	j = tmp->i;
	e = env;
	while (str[j])
	{
		if (str[j] == ' ' || str[j] == '\"' || str[j] == '\'' || str[j] == '\\')
			break ;
		j++;
	}
	tm = malloc(sizeof(char) * (j - tmp->i) + 1);
	cle(tm, str, tmp, j);
	while (e)
	{
		if (!(ft_strcmp(tm, e->key)))
			break ;
		e = e->next;
	}
	envp(e, s, tmp);
	if (tm)
		free(tm);
}

static	char			*func(t_tok *pnt, t_config *cnf)
{
	int		len;
	t_arg	*args;
	t_env	*env;
	char	*ret;

	env = cnf->envl;
	len = specstrlen(pnt->func, cnf);
	while (len == 0 && pnt->arg)
	{
		env = cnf->envl;
		args = pnt->arg;
		free(pnt->func);
		pnt->func = ft_strdup(args->sarg);
		pnt->qfunc = args->quote;
		len = specstrlen(pnt->func, cnf);
		pnt->arg = pnt->arg->next;
		free(args->sarg);
		free(args);
		if (pnt->qfunc == 1)
			return (ft_strdup(pnt->func));
	}
	ret = namefunc(cnf, pnt, len);
	return (ret);
}

char					*getname(t_config *cnf, t_tok *pnt)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (pnt->qfunc == 1)
		return (ft_strdup(pnt->func));
	else
		ret = func(pnt, cnf);
	return (ret);
}
