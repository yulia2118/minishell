/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:44:23 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/22 12:44:25 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				issep(char c)
{
	if (c == ';' || c == ' ' || c == '|')
		return (1);
	return (0);
}

static	int		in(char *line, int i, t_tok *tok, int j)
{
	int	count;

	count = 0;
	while (line[i] && i < j)
	{
		tok->prdir[count] = line[i];
		count++;
		i++;
	}
	tok->prdir[count] = 0;
	return (i);
}

static	int		prdir(t_tok *tok, char *line, int i)
{
	int		count;
	t_tmp	tmp;

	count = 0;
	tmp.eq = 0;
	tmp.st = 0;
	i = ft_skipspace(line, i);
	tmp.j = i;
	while (line[tmp.j])
	{
		tmp.eq = checkqq(line, tmp.j, tmp.eq, &tmp);
		if ((tmp.eq == 0 && issep(line[tmp.j]) && tmp.st == 0)
			|| (tmp.eq == 0 && isredir(line[tmp.j]) && tmp.st == 0))
			break ;
		ccn(line, &tmp, tmp.j, tmp.eq);
		count++;
		tmp.j++;
	}
	if (!(tok->prdir = malloc(sizeof(char) * count + 1)))
		return (-1);
	i = in(line, i, tok, tmp.j);
	return (i);
}

int				skipsep(t_tok *tok, char *line, int i)
{
	if (line[i] == ';')
	{
		tok->tsep = 0;
		i++;
	}
	else if (line[i] == '|')
	{
		tok->tsep = 1;
		i++;
	}
	i = ft_skipspace(line, i);
	return (i);
}

int				redir(char *line, int i, t_tok *tok)
{
	if (line[i] == '<')
	{
		tok->rdir = 1;
		i++;
		if ((i = prdir(tok, line, i)) < 0)
			return (-1);
	}
	else if (line[i] && (line[i] == '>' && line[i + 1] == '>'))
	{
		tok->rdir = 3;
		i += 2;
		if ((i = prdir(tok, line, i)) < 0)
			return (-1);
	}
	else if (line[i] == '>')
	{
		tok->rdir = 2;
		i++;
		if ((i = prdir(tok, line, i)) < 0)
			return (-1);
	}
	return (i);
}
