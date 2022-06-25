/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toks.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:03:53 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/21 20:03:55 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int				args(char *line, int i, t_tok *tok)
{
	t_arg *farg;
	t_arg *sarg;

	farg = NULL;
	sarg = NULL;
	while (line[i])
	{
		i = ft_skipspace(line, i);
		if (line[i] == '\0' || (issep(line[i]) && line[i - 1] != '\\'))
			break ;
		if (isredir(line[i]))
			i = addredir(tok, i, line);
		if (!(farg = getarg(line, &i)))
			return (-1);
		farg->prev = sarg;
		if (sarg)
			sarg->next = farg;
		sarg = farg;
	}
	while (farg && farg->prev)
		farg = farg->prev;
	tok->arg = farg;
	return (i);
}

static	t_tok			*in(void)
{
	t_tok *tok;

	if (!(tok = malloc(sizeof(t_tok))))
		return (NULL);
	tok->qfunc = 0;
	tok->rdir = 0;
	tok->tsep = 0;
	tok->arg = NULL;
	tok->next = NULL;
	tok->prdir = NULL;
	tok->ndir = NULL;
	return (tok);
}

static	int				bk(int i, char *line)
{
	if (issep(line[i]))
	{
		if (i == 0 || (i > 0 && line[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

static	t_tok			*newtok(char *line, int *i)
{
	t_tok	*tok;

	if (!(tok = in()))
		return (NULL);
	if (isredir(line[*i]))
		*i = addredir(tok, *i, line);
	if ((*i = funcname(line, *i, tok)) < 0)
		return (NULL);
	while (line[*i])
	{
		*i = ft_skipspace(line, *i);
		if (bk(*i, line))
			break ;
		if ((*i = redir(line, *i, tok)) < 0)
			return (NULL);
		if ((line[*i] == ';' && line[*i - 1] != '\\')
			|| (line[*i] == '|' && line[*i - 1] != '\\'))
			break ;
		if ((*i = args(line, *i, tok)) < 0)
			return (NULL);
		if (bk(*i, line))
			break ;
	}
	return (tok);
}

t_tok					*analys(char *line)
{
	int		i;
	t_tok	*ftok;
	t_tok	*stok;

	i = 0;
	stok = NULL;
	ftok = NULL;
	i = ft_skipspace(line, i);
	while (line[i])
	{
		if (stok)
			i = skipsep(stok, line, i);
		if (line[i] == '\0')
			break ;
		ftok = newtok(line, &i);
		ftok->prev = stok;
		if (stok)
			stok->next = ftok;
		stok = ftok;
		i = ft_skipspace(line, i);
	}
	while (ftok && ftok->prev)
		ftok = ftok->prev;
	free(line);
	return (ftok);
}
