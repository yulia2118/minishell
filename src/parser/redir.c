/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:28:06 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/04 12:28:08 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int		typedir(char *line, int i)
{
	int	type;

	type = 0;
	if (line[i] == '<')
		type = 1;
	else if (line[i] && (line[i] == '>' && line[i + 1] == '>'))
		type = 3;
	else if (line[i] == '>')
		type = 2;
	return (type);
}

int				checkq(char *line, int i, int eq)
{
	if ((line[i] == '\'' && eq == 0))
	{
		if (i > 0 && line[i - 1] == '\\')
			eq = 0;
		else
			eq = 1;
	}
	else if ((line[i] == '\"' && eq == 0))
	{
		if (i > 0 && line[i - 1] == '\\')
			eq = 0;
		else
			eq = 2;
	}
	else if ((line[i] == '\'' && eq == 1))
		eq = 0;
	else if ((line[i] == '\"' && eq == 2))
	{
		if (i > 0 && line[i - 1] == '\\')
			eq = 2;
		else
			eq = 0;
	}
	return (eq);
}

static	int		in(char *line, int i, t_rdir *tmp, int j)
{
	int count;

	count = 0;
	while (line[i] && i < j)
	{
		tmp->prdir[count] = line[i];
		count++;
		i++;
	}
	tmp->prdir[count] = 0;
	return (i);
}

int				getpth(t_rdir *tmp, char *line, int i)
{
	t_tmp	tm;
	int		count;

	tm.eq = 0;
	count = 0;
	i = ft_skipspace(line, i);
	tm.j = i;
	tm.st = 0;
	while (line[tm.j])
	{
		ccn(line, &tm, tm.j, tm.eq);
		tm.eq = checkqq(line, tm.j, tm.eq, &tm);
		if ((tm.eq == 0 && issep(line[tm.j]) && tm.st == 0)
			|| (tm.eq == 0 && isredir(line[tm.j]) && tm.st == 0))
			break ;
		count++;
		tm.j++;
	}
	tmp->prdir = malloc(sizeof(char) * count + 1);
	i = in(line, i, tmp, tm.j);
	return (i);
}

int				addredir(t_tok *tok, int i, char *line)
{
	t_rdir	*tmp;
	t_rdir	*sc;

	if (!tok->prdir)
		i = redir(line, i, tok);
	else
	{
		sc = tok->ndir;
		while (sc && sc->next)
			sc = sc->next;
		if (!(tmp = malloc(sizeof(t_rdir))))
			return (i);
		tmp->type = typedir(line, i);
		if (tmp->type == 1 || tmp->type == 2)
			i++;
		else
			i += 2;
		i = getpth(tmp, line, i);
		tmp->next = NULL;
		if (sc)
			sc->next = tmp;
		else
			tok->ndir = tmp;
	}
	return (i);
}
