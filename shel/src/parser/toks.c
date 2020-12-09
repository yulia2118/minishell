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

static	int				funcname(char *line, int i, t_tok *tok)
{
	int		endn;
	int		j;
	int		eq;

	endn = 0;
	j = i;
	eq = 0;
	while (line[j])
	{
		if ((line[j] == '\'' && eq == 0))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 0;
			else
				eq = 1;
		}
		else if ((line[j] == '\"' && eq == 0))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 0;
			else
				eq = 2;
		}
		else if ((line[j] == '\'' && eq == 1))
			eq = 0;
		else if ((line[j] == '\"' && eq == 2))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 2;
			else
				eq = 0;
		}
		if (eq == 0 && issep(line[j]))
		{
			if (j == 0 || (j > 0 && line[j - 1] != '\\'))
				break ;
		}
		if (eq == 0 && (line[j] == '\'' || line[j] == '\"'))
			endn--;
		endn++;
		j++;
	}
	if (!(tok->func = malloc(sizeof(char) * endn + 1)))
		return (-1);
	endn = 0;
	while (line[i] && i < j)
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
			if (j > 0 && line[i - 1] == '\\')
				eq = 2;
			else
				eq = 0;
		}
		tok->func[endn] = line[i];
		if ((i == 0 && line[i] == '\\' && eq == 0) || (i != 0
			&& (line[i] == '\\' && line[i - 1] != '\\') && eq == 0))
			endn--;
		if ((line[i] == '\'' || line[i] == '\"') && eq == 0)
		{
			if (i != 0 && line[i - 1] != '\\')
				endn--;
		}
		if (line[i] == '\'' && eq == 1)
		{
			if (i != 0 && line[i - 1] != '\\')
				endn--;
			else if (i == 0)
				endn--;
		}
		if (line[i] == '\"' && eq == 2)
		{
			if (i != 0 && line[i - 1] != '\\')
				endn--;
			else if (i == 0)
				endn--;
		}
		i++;
		endn++;
	}
	tok->func[endn] = 0;
	return (i);
}

static	int				argqt(t_arg *arg, char *line, int i)
{
	arg->quote = 0;
	if (line[i] == '\'')
		arg->quote = 1;
	if (line[i] == '\"')
		arg->quote = 2;
	return (i);
}

static	t_arg			*getarg(char *line, int *i)
{
	t_arg	*arg;
	int		arglen;
	int		j;
	int		eq;
	int		q;

	arglen = 0;
	if (!(arg = malloc(sizeof(t_arg))))
		return (NULL);
	arg->next = NULL;
	arg->prev = NULL;
	*i = argqt(arg, line, *i);
	eq = arg->quote;
	if (eq != 0)
		*i += 1;
	j = *i;
	while (line[j])
	{
		if (issep(line[j]) && eq == 0)
		{
			if (j == 0 || (j > 0 && line[j - 1] != '\\'))
				break ;
		}
		if ((line[j] == '\'' && eq == 0))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 0;
			else
				eq = 1;
		}
		else if ((line[j] == '\"' && eq == 0))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 0;
			else
				eq = 2;
		}
		else if ((line[j] == '\'' && eq == 1))
			eq = 0;
		else if ((line[j] == '\"' && eq == 2))
		{
			if (j > 0 && line[j - 1] == '\\')
				eq = 2;
			else
				eq = 0;
		}
		if (eq == 0 && isredir(line[j]))
			break ;
		arglen++;
		j++;
	}
	if (!(arg->sarg = malloc(sizeof(char) * arglen + 1)))
		return (NULL);
	arglen = 0;
	eq = arg->quote;
	q = *i;
	while (line[*i] && q < j)
	{
		arg->sarg[arglen] = line[q];
		q++;
		arglen++;
	}
	*i = j;
	if (eq == 0)
		arg->sarg[arglen] = 0;
	if (eq != 0)
		arg->sarg[arglen - 1] = 0;
	return (arg);
}

static	int		args(char *line, int i, t_tok *tok)
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

static	t_tok			*newtok(char *line, int *i)
{
	t_tok	*tok;

	if (!(tok = malloc(sizeof(t_tok))))
		return (NULL);
	tok->qfunc = 0;
	tok->rdir = 0;
	tok->tsep = 0;
	tok->arg = NULL;
	tok->next = NULL;
	tok->prdir = NULL;
	tok->ndir = NULL;
	if (isredir(line[*i]))
		*i = addredir(tok, *i, line);
	if ((*i = funcname(line, *i, tok)) < 0)
		return (NULL);
	while (line[*i])
	{
		*i = ft_skipspace(line, *i);
		if (issep(line[*i]))
		{
			if (*i == 0 || (*i > 0 && line[*i - 1] != '\\'))
				break ;
		}
		if ((*i = redir(line, *i, tok)) < 0)
			return (NULL);
		if ((line[*i] == ';' && line[*i - 1] != '\\')
			|| (line[*i] == '|' && line[*i - 1] != '\\'))
			break ;
		if ((*i = args(line, *i, tok)) < 0)
			return (NULL);
		if (issep(line[*i]))
		{
			if (*i == 0 || (*i > 0 && line[*i - 1] != '\\'))
				break ;
		}
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
