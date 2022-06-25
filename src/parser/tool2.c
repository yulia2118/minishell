/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:14:54 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/10 18:17:21 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				isredir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

static	int		rec(char *line, int i, t_tmp *tmp, t_tok *tok)
{
	int endn;

	endn = 0;
	while (line[i] && i < tmp->j)
	{
		tok->func[endn] = line[i];
		i++;
		endn++;
	}
	tok->func[endn] = 0;
	return (i);
}

int				funcname(char *line, int i, t_tok *tok)
{
	int		endn;
	t_tmp	tmp;

	endn = 0;
	tmp.j = i;
	tmp.eq = 0;
	tmp.st = 0;
	while (line[tmp.j])
	{
		ccn(line, &tmp, tmp.j, tmp.eq);
		tmp.eq = checkqq(line, tmp.j, tmp.eq, &tmp);
		if ((tmp.eq == 0 && issep(line[tmp.j]) && tmp.st == 0)
			|| (tmp.eq == 0 && isredir(line[tmp.j]) && tmp.st == 0))
			break ;
		endn++;
		tmp.j++;
	}
	if (!(tok->func = malloc(sizeof(char) * endn + 1)))
		return (-1);
	i = rec(line, i, &tmp, tok);
	return (i);
}
