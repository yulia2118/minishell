/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:51:07 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 11:51:09 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void		fred(t_rdir *tmp)
{
	free(tmp->prdir);
	free(tmp);
}

static	int			cyclerdir(t_tok *pnt, t_config *cnf)
{
	t_rdir	*tmp;

	if (pnt->rdir != 0)
	{
		while (pnt->ndir)
		{
			tmp = pnt->ndir;
			free(pnt->prdir);
			pnt->prdir = gettruepth(tmp->prdir, cnf);
			pnt->rdir = tmp->type;
			if (pnt->rdir == 1)
			{
				if (!(inp(cnf, pnt)))
					return (0);
			}
			else if (pnt->rdir == 2 || pnt->rdir == 3)
			{
				if (!(dir(cnf, pnt)))
					return (0);
			}
			pnt->ndir = pnt->ndir->next;
			fred(tmp);
		}
	}
	return (1);
}

static	int			ccnd(t_tok *pnt, t_config *cnf)
{
	if (!cyclerdir(pnt, cnf))
		return (0);
	if (pnt->rdir == 0 && pnt->tsep == 1 && cnf->child == 0)
		pnt = gopipe(pnt, cnf);
	if (cnf->child == 1)
		pipedir(pnt, cnf);
	if (cnf->child == 2 || cnf->child == 0)
		preex(cnf, pnt);
	return (1);
}

int					pipedir(t_tok *pnt, t_config *cnf)
{
	char	*s;

	if (cnf->child == 1)
		cnf->child = 2;
	if (pnt->rdir == 1)
	{
		s = gettruepth(pnt->prdir, cnf);
		free(pnt->prdir);
		pnt->prdir = s;
		if (!(inp(cnf, pnt)))
			return (0);
	}
	else if (pnt->rdir == 2 || pnt->rdir == 3)
	{
		s = gettruepth(pnt->prdir, cnf);
		free(pnt->prdir);
		pnt->prdir = s;
		if (!(dir(cnf, pnt)))
			return (0);
	}
	if (!(ccnd(pnt, cnf)))
		return (0);
	cnf->child = 3;
	return (1);
}
