/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:44:37 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/02 17:44:39 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			freetok(t_tok *tok)
{
	t_tok	*tmp;
	t_arg	*targ;

	while (tok)
	{
		tmp = tok;
		while (tok->arg)
		{
			if (tok->arg->sarg)
				free(tok->arg->sarg);
			targ = tok->arg;
			tok->arg = tok->arg->next;
			free(targ);
		}
		if (tok->func)
			free(tok->func);
		if (tok->prdir)
			free(tok->prdir);
		tok = tok->next;
		free(tmp);
	}
}

void			freeenvl(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		env = env->next;
		free(tmp);
	}
}

static	int		lentarg(char **targ)
{
	int i;

	i = 0;
	while (targ[i])
		i++;
	return (i);
}

static	void	ext(int c, int t, t_config *cnf, char **targ)
{
	if (c == 2 && t == 0)
		cnf->excode = ft_atoi(targ[1]);
	else if (c >= 2 && t != 0)
	{
		cnf->excode = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(targ[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		cnf->excode = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
}

void			ft_exit(t_config *cnf, char **targ)
{
	int	i;
	int t;
	int c;

	t = 0;
	i = 0;
	cnf->exit = 0;
	if (cnf->pipe.cp == 0)
		ft_putstr_fd("exit\n", 2);
	if ((c = lentarg(targ)) > 1)
	{
		while (targ[1][i])
		{
			if (!(ft_isdigit(targ[1][i])))
				t = 1;
			i++;
		}
		ext(c, t, cnf, targ);
	}
	else
		cnf->excode = 0;
}
