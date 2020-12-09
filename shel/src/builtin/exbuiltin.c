/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:40:41 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/30 21:40:43 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		isbuilt(char *name)
{
	if (!ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "echo"))
		return (1);
	if (!ft_strcmp(name, "pwd"))
		return (1);
	if (!ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "unset"))
		return (1);
	if (!ft_strcmp(name, "env"))
		return (1);
	return (0);
}

int		gobuiltin(t_config *cnf, t_tok *pnt, char **targ)
{
	if (!ft_strcmp(pnt->func, "cd"))
		cnf->excode = ft_cd(targ, cnf->env);
	if (!ft_strcmp(pnt->func, "echo"))
		cnf->excode = ft_echo(targ);
	if (!ft_strcmp(pnt->func, "pwd"))
		cnf->excode = ft_pwd();
	if (!ft_strcmp(pnt->func, "export"))
	{
		//if (targ && targ[1] && !targ[2])
			//cnf->excode = ft_export(targ ,cnf->env);
		//else if (targ && targ[1] && targ[2])
			cnf->excode = ft_export(targ, cnf->env);
	}
	if (!ft_strcmp(pnt->func, "unset"))
		cnf->excode = ft_unset(targ, cnf->env);
	if (!ft_strcmp(pnt->func, "env"))
		cnf->excode = ft_env(cnf->env);
	return (0);
}
