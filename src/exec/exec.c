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

static	int			ccl(t_config *cnf, t_arg *tmp, char **args, int i)
{
	args[i] = getstr(tmp, cnf);
	if (!args[i])
		i--;
	if (!args[i][0])
	{
		free(args[i]);
		i--;
	}
	i++;
	return (i);
}

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
		i = ccl(cnf, tmp, args, i);
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void				preex(t_config *cnf, t_tok *pnt)
{
	char	**targ;
	int		i;

	i = 0;
	targ = NULL;
	targ = argtomatrix(pnt, cnf);
	if (targ && targ[0] && !(ft_strcmp(targ[0], "exit"))
		&& (cnf->pipe.cp != 0 && cnf->pipe.i == 0))
		cnf->err = 2;
	if (targ && targ[0] && !(ft_strcmp(targ[0], "exit")) && cnf->err == 0)
		ft_exit(cnf, targ);
	else if (targ && targ[0] && isbuilt(targ[0])
		&& cnf->exit && cnf->err == 0)
		gobuiltin(cnf, targ);
	else if (targ && targ[0] && cnf->exit && cnf->err == 0)
		cnf->excode = goexec(cnf, pnt, targ);
	tf(targ);
}

static	void		wtp(t_config *cnf)
{
	int		status;

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
	if (cnf->pipe.cp)
	{
		tif(cnf->pipe.pipefd);
		free(cnf->pipe.pid);
	}
}

void				exec(t_config *cnf)
{
	t_tok	*pnt;
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
		wtp(cnf);
		while (i < cnf->pipe.cp)
		{
			pnt = pnt->next;
			i++;
		}
		tf(cnf->env);
		cnf->env = cpyenv(cnf);
		pnt = pnt->next;
	}
}
