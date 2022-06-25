/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:24:54 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/14 16:25:38 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		check2(t_config *cnf, char *line, int i, t_tmp *tmp)
{
	if (i != 0 && line[i] == '|' && line[i + 1] == ';'
		&& tmp->st == 0 && tmp->eq == 0)
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token ';'\n", 2);
		return (1);
	}
	if (i != 0 && (line[i] == ';' || line[i] == '|')
		&& tmp->st == 0 && tmp->eq == 0)
	{
		i = ft_skipspace(line, ++i);
		if (line[i] == '|')
		{
			cnf->excode = 258;
			ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
			return (1);
		}
		if (line[i] == ';')
		{
			cnf->excode = 258;
			ft_putstr_fd("syntax error near unexpected token ';'\n", 2);
			return (1);
		}
	}
	return (0);
}

static	int		sclerr(t_config *cnf, char *line, int i, t_tmp *tmp)
{
	if (i != 0 && line[i] == ';' && line[i + 1] == ';'
		&& tmp->st == 0 && tmp->eq == 0)
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token ';;'\n", 2);
		return (1);
	}
	if (i != 0 && line[i] == '|' && line[i + 1] == '|'
		&& tmp->st == 0 && tmp->eq == 0)
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token '||'\n", 2);
		return (1);
	}
	if (i != 0 && line[i] == ';' && line[i + 1] == '|'
		&& tmp->st == 0 && tmp->eq == 0)
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	if (check2(cnf, line, i, tmp))
		return (1);
	return (0);
}

static	int		check1(char *line, int i, t_config *cnf)
{
	if (line && line[0] == '\\' && line[1] == '\0')
	{
		ft_putstr_fd("\e[1;38;5;202msyntax error multiline command\e[0m\n", 2);
		cnf->excode = 258;
		return (1);
	}
	if (line && i == 0 && line[i] == '|' && line[i + 1] == '|')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token '||'\n", 2);
		return (1);
	}
	if (line && i == 0 && line[i] == ';' && line[i + 1] == ';')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token ';;'\n", 2);
		return (1);
	}
	return (0);
}

static	int		check3(t_config *cnf, char *line, int i, t_tmp *tmp)
{
	if (i != 0 && line[i] == '|' && tmp->st == 0 && tmp->eq == 0)
	{
		i = ft_skipspace(line, ++i);
		if (!line[i])
		{
			ft_putstr_fd("syntax error multiline command\n", 2);
			cnf->excode = 258;
			return (1);
		}
	}
	return (0);
}

int				checkunexp(t_config *cnf, char *line)
{
	int		i;
	t_tmp	tmp;

	i = 0;
	tmp.st = 0;
	tmp.eq = 0;
	if (check1(line, i, cnf))
		return (1);
	while (line[i])
	{
		tmp.eq = chckqte(line, i, &tmp, tmp.eq);
		if (sclerr(cnf, line, i, &tmp))
			return (1);
		if (check3(cnf, line, i, &tmp))
			return (1);
		ccn(line, &tmp, i, tmp.eq);
		i++;
	}
	return (0);
}
