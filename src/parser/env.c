/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:22:22 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/28 14:22:24 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	inclvl(t_config *cnf)
{
	t_env	*tmp;
	int		actlvl;

	tmp = cnf->envl;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, "SHLVL")))
			break ;
		tmp = tmp->next;
	}
	actlvl = ft_atoi(tmp->value);
	actlvl++;
	free(tmp->value);
	tmp->value = ft_itoa(actlvl);
}

static	void	cl(t_config *cnf, t_env *list, char **env, int type)
{
	char **tmp;

	if (type == 0)
		cnf->envl = list;
	if (type == 1)
		cnf->senvl = list;
	list->next = NULL;
	tmp = ft_frstsplit(env[0], '=');
	list->key = tmp[0];
	list->value = tmp[1];
	free(tmp);
}

void			envtolist(t_config *cnf, char **env, int type)
{
	t_env	*next;
	t_env	*list;
	char	**tmp;
	int		i;

	i = 1;
	if (!(env))
		return ;
	if (!(list = malloc(sizeof(t_env))))
		return ;
	cl(cnf, list, env, type);
	while (env && env[i])
	{
		if (!(next = malloc(sizeof(t_env))))
			return ;
		tmp = ft_frstsplit(env[i], '=');
		next->key = tmp[0];
		next->value = tmp[1];
		next->next = NULL;
		list->next = next;
		list = next;
		i++;
		free(tmp);
	}
}

char			**cpyenv(t_config *cnf)
{
	t_env	*tmp;
	char	*s;
	char	**tab;
	int		i;
	int		j;

	j = 0;
	i = lenenv(cnf->envl);
	tmp = cnf->envl;
	if (!(tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		s = ft_strjoin(tmp->key, "=");
		tab[j] = ft_strjoin(s, tmp->value);
		free(s);
		j++;
		tmp = tmp->next;
	}
	tab[j] = NULL;
	return (tab);
}

void			init(t_config *cnf, char **env)
{
	cnf->exit = 1;
	cnf->in = dup(0);
	cnf->out = dup(1);
	cnf->pipein = -1;
	cnf->pipeout = -1;
	cnf->savein = -1;
	cnf->saveout = -1;
	cnf->envl = NULL;
	cnf->env = NULL;
	envtolist(cnf, env, 0);
	envtolist(cnf, env, 1);
	inclvl(cnf);
	cnf->env = cpyenv(cnf);
}
