/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:59:08 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/26 17:59:09 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char		**argtomatrix(t_tok *pnt, t_config *cnf)
{
	char	**args;
	t_arg	*tmp;
	int		j;
	int		i;

	i = 1;
	j = countargs(pnt->arg);
	tmp = pnt->arg;
	if (!(args = malloc(sizeof(char *) * (j + 2))))
		return (NULL);
	args[0] = getname(cnf, pnt);
	if (!args || !args[0] || !args[0][0])
	{
		cnf->err = 1;
		return (NULL);
	}
	tmp = pnt->arg;
	while (tmp && i < j + 1)
	{
		args[i] = getstr(tmp, cnf->envl, cnf);
		if (!args[i])
			i--;
		if (!args[i][0])
		{
			free(args[i]);
			i--;
		}
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

static	void		preex(t_config *cnf, t_tok *pnt)
{
	char	**targ;
	int		i;

	i = 0;
	targ = NULL;
	targ = argtomatrix(pnt, cnf);
	if (pnt->func && !(ft_strcmp(pnt->func, "exit"))
		&& (cnf->pipe.cp != 0 && cnf->pipe.i == 0))
		cnf->err = 2;
	if (pnt->func && !(ft_strcmp(pnt->func, "exit")) && cnf->err == 0)
		ft_exit(cnf, targ);
	else if (targ && pnt->func && isbuilt(pnt->func)
		&& cnf->exit && cnf->err == 0)
		gobuiltin(cnf, pnt, targ);
	else if (pnt->func && cnf->exit && cnf->err == 0)
		cnf->excode = goexec(cnf, pnt, targ);
	tf(targ);
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
			pnt->prdir = gettruepth(tmp->prdir, cnf->envl, cnf);
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
			free(tmp->prdir);
			free(tmp);
		}
	}
	return (1);
}

int					pipedir(t_tok *pnt, t_config *cnf)
{
	int		pipe;
	char	*s;

	pipe = 0;
	if (cnf->child == 1)
		cnf->child = 2;
	if (pnt->rdir == 1)
	{
		s = gettruepth(pnt->prdir, cnf->envl, cnf);
		free(pnt->prdir);
		pnt->prdir = s;
		if (!(inp(cnf, pnt)))
			return (0);
	}
	else if (pnt->rdir == 2 || pnt->rdir == 3)
	{
		s = gettruepth(pnt->prdir, cnf->envl, cnf);
		free(pnt->prdir);
		pnt->prdir = s;
		if (!(dir(cnf, pnt)))
			return (0);
	}
	if (!cyclerdir(pnt, cnf))
		return (0);
	if (pnt->rdir == 0 && pnt->tsep == 1 && cnf->child == 0)
		pnt = gopipe(pnt, cnf);
	if (cnf->child == 1)
		pipedir(pnt, cnf);
	if (cnf->child == 2 || cnf->child == 0)
		preex(cnf, pnt);
	cnf->child = 3;
	return (1);
}

void				exec(t_config *cnf)
{
	t_tok	*pnt;
	int		status;
	int		i;

	pnt = cnf->tok;
	while (pnt)
	{
		i = 0;
		cnf->pipe.cp = 0;
		cnf->err = 0;
		cnf->child = 0;
		pipedir(pnt, cnf);
		savefd(cnf);
		closefds(cnf);
		resetfds(cnf);
		if (cnf->pipe.cp != 0 && ((cnf->pipe.i != 0 &&
			cnf->pipe.pid[cnf->pipe.i - 1] == 0)
			|| cnf->pipe.pid[cnf->pipe.i] == 0))
			exit(cnf->excode);
		if (cnf->pipe.cp != 0)
		{
			waitpid(-1, &status, 0);
			cnf->excode = WEXITSTATUS(status);
		}
		if (cnf->pipe.cp != 0 && ((cnf->pipe.i != 0 &&
			cnf->pipe.pid[cnf->pipe.i - 1] == 0)
				|| cnf->pipe.pid[cnf->pipe.i] == 0))
			exit(cnf->excode);
		while (i < cnf->pipe.cp)
		{
			pnt = pnt->next;
			i++;
		}
		if (cnf->pipe.cp)
		{
			tif(cnf->pipe.pipefd);
			free(cnf->pipe.pid);
		}
		cnf->envl = freeenv(cnf->envl);
		envtolist(cnf, cnf->env);
		pnt = pnt->next;
	}
}
