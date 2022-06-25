/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:33:31 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/15 14:33:32 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		check3(t_config *cnf, char *line, t_tmp *tmp)
{
	if (line[tmp->j] == '<')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (1);
	}
	if (line[tmp->j] == ';')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
		return (1);
	}
	if (line[tmp->j] == '|')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

static	int		check2(t_config *cnf, char *line, t_tmp *tmp)
{
	if (!line[tmp->j])
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (line[tmp->j] == '>' && line[tmp->j + 1] == '>')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (1);
	}
	if (line[tmp->j] == '>')
	{
		cnf->excode = 258;
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	return (0);
}

static	int		check1(t_config *cnf, char *line, int i, t_tmp *tmp)
{
	if ((line[i] == '>' || line[i] == '<') && tmp->st == 0 && tmp->eq == 0)
	{
		if (line[i + 1] == '>')
			i++;
		tmp->j = ft_skipspace(line, ++i);
		if (check2(cnf, line, tmp))
			return (1);
		if (check3(cnf, line, tmp))
			return (1);
	}
	return (0);
}

int				cherrdir(char *line, t_config *cnf)
{
	int		i;
	t_tmp	tmp;

	i = 0;
	tmp.st = 0;
	tmp.eq = 0;
	while (line[i])
	{
		tmp.j = 0;
		tmp.eq = chckqte(line, i, &tmp, tmp.eq);
		if (check1(cnf, line, i, &tmp))
			return (1);
		ccn(line, &tmp, i, tmp.eq);
		i++;
	}
	return (0);
}
