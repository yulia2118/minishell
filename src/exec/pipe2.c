/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:21:24 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 12:21:26 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				cpipes(t_tok *pnt)
{
	t_tok	*tmp;
	int		i;

	i = 0;
	tmp = pnt;
	while (tmp && tmp->tsep == 1)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static	void	ons(t_config *cnf)
{
	int i;

	i = 0;
	while (i < cnf->pipe.cp)
	{
		cnf->pipe.pid[i] = -1;
		i++;
	}
}

void			intil(t_config *cnf, t_tok *pnt)
{
	int i;

	i = 0;
	cnf->pipe.cp = cpipes(pnt);
	cnf->pipe.pid = malloc(sizeof(pid_t) * cnf->pipe.cp);
	ons(cnf);
	cnf->pipe.pipefd = malloc(sizeof(int*) * (cnf->pipe.cp + 1));
	cnf->pipe.pipefd[cnf->pipe.cp] = NULL;
	while (i < cnf->pipe.cp)
	{
		cnf->pipe.pipefd[i] = malloc(sizeof(int) * 2);
		cnf->pipe.pipefd[i][0] = -1;
		cnf->pipe.pipefd[i][1] = -1;
		i++;
	}
}
