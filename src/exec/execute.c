/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:55:00 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/29 23:55:02 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char		*srchpth(char *pb, char *func)
{
	DIR				*cat;
	struct dirent	*rec;
	char			*allp;
	char			*tmp;

	allp = NULL;
	if (!(cat = opendir(pb)))
		return (NULL);
	while ((rec = readdir(cat)) != NULL)
	{
		if (!(ft_strcmp(rec->d_name, func)))
		{
			tmp = ft_strjoin(pb, "/");
			allp = ft_strjoin(tmp, rec->d_name);
			free(tmp);
		}
	}
	closedir(cat);
	return (allp);
}

static int			is_absolute_path(char *path)
{
	struct stat	s;

	if (!(stat(path, &s)))
		return (1);
	return (0);
}

static	int			cond(t_config *cnf, char **targ, char *p)
{
	int status;

	status = 127;
	if (is_absolute_path(targ[0]) && !p)
		status = bin(targ[0], targ, cnf);
	else if (p != NULL)
		status = bin(p, targ, cnf);
	else
		status = bin(p, targ, cnf);
	return (status);
}

int					goexec(t_config *cnf, t_tok *pnt, char **targ)
{
	int		status;
	int		i;
	char	*p;
	char	**tp;
	t_env	*env;

	i = 0;
	p = NULL;
	tp = NULL;
	env = cnf->envl;
	status = 127;
	while (env && env->key && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if (env != NULL)
	{
		tp = ft_split(env->value, ':');
		if (!(pnt->func) && !tp[0])
			return (1);
		while (pnt->func && tp[i] && p == NULL)
			p = srchpth(tp[i++], targ[0]);
	}
	status = cond(cnf, targ, p);
	free(p);
	tf(tp);
	return (status);
}
