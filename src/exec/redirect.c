/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:32:06 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/26 22:32:08 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		inp(t_config *cnf, t_tok *pnt)
{
	closefd(cnf->savein);
	cnf->savein = open(pnt->prdir, O_RDONLY, S_IRWXU);
	if (cnf->in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pnt->prdir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	dup2(cnf->savein, 0);
	return (1);
}

int		dir(t_config *cnf, t_tok *pnt)
{
	closefd(cnf->saveout);
	if (pnt->rdir == 2)
		cnf->saveout = open(pnt->prdir, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (pnt->rdir == 3)
		cnf->saveout = open(pnt->prdir, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (cnf->out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pnt->prdir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	dup2(cnf->saveout, 1);
	return (1);
}
