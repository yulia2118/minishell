/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:58:06 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/30 22:58:08 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	savefd(t_config *cnf)
{
	dup2(cnf->in, 0);
	dup2(cnf->out, 1);
}

void	closefds(t_config *cnf)
{
	closefd(cnf->pipein);
	closefd(cnf->pipeout);
	closefd(cnf->savein);
	closefd(cnf->saveout);
}

void	resetfds(t_config *cnf)
{
	cnf->savein = -1;
	cnf->saveout = -1;
	cnf->saveout = -1;
	cnf->savein = -1;
	cnf->pipein = -1;
	cnf->pipeout = -1;
}

void	closefd(int fd)
{
	if (fd > 0)
		close(fd);
}
