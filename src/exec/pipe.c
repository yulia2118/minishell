/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:43:32 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/05 12:43:33 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	cp(t_config *cnf, int i)
{
	cnf->child = 1;
	closefd(cnf->pipe.pipefd[i][1]);
	dup2(cnf->pipe.pipefd[i][0], 0);
}

static	void	pp(t_config *cnf, int i)
{
	cnf->child = 1;
	closefd(cnf->pipe.pipefd[i][0]);
	dup2(cnf->pipe.pipefd[i][1], 1);
	cnf->pipeout = cnf->pipe.pipefd[i][1];
}

t_tok			*gopipe(t_tok *pnt, t_config *cnf)
{
	int i;

	i = 0;
	intil(cnf, pnt);
	while (i < cnf->pipe.cp)
	{
		cnf->pipe.i = i;
		pipe(cnf->pipe.pipefd[i]);
		cnf->pipe.pid[i] = fork();
		if (cnf->pipe.pid[i] == 0)
		{
			cnf->excode = 0;
			cp(cnf, i);
			cnf->pipein = cnf->pipe.pipefd[i][0];
			pnt = pnt->next;
		}
		else
			pp(cnf, i);
		if (cnf->pipe.pid[i] != 0)
			break ;
		i++;
	}
	return (pnt);
}
