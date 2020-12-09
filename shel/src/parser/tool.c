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

static	int		prdir(t_tok *tok, char *line, int i)
{
	int	j;
	int count;
	int oq;

	count = 0;
	oq = 0;
	i = ft_skipspace(line, i);
	j = i;
	while (line[j])
	{
		oq = checkq(line, j, oq);
		if (oq == 0 && issep(line[j]))
			break ;
		count++;
		j++;
	}
	if (!(tok->prdir = malloc(sizeof(char) * count + 1)))
		return (-1);
	count = 0;
	while (line[i] && i < j)
	{
		oq = checkq(line, i, oq);
		tok->prdir[count] = line[i];
		count++;
		i++;
	}
	tok->prdir[count] = 0;
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
