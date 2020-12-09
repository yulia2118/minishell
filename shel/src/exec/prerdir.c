/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prerdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:17:49 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/08 12:17:51 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*gettruepth(char *str, t_env *env, t_config *cnf)
{
	char	*ret;
	int		len;
	int		i;
	int		j;
	int		eq;
	char	*ss;
	int		k;

	i = 0;
	j = 0;
	eq = 0;
	len = specstrlen(str, env, cnf);
	ret = malloc(sizeof(char) * len + 1);
	while (str[i])
	{
		k = 0;
		eq = checkq(str, i, eq);
		if (((str[i] != '$') || (i != 0 && str[i] == '$'
			&& str[i - 1] == '\\')) || eq == 1)
			ret[j] = str[i];
		if ((i == 0 && str[i] == '\\' && eq == 0) || (i != 0
			&& (str[i] == '\\' && str[i - 1] != '\\') && eq == 0))
			j--;
		if ((str[i] == '\'' || str[i] == '\"') && eq == 0)
		{
			if (i != 0 && str[i - 1] != '\\')
				j--;
		}
		if (str[i] == '\'' && eq == 1)
		{
			if (i != 0 && str[i - 1] != '\\')
				j--;
			else if (i == 0)
				j--;
		}
		if (str[i] == '\"' && eq == 2)
		{
			if (i != 0 && str[i - 1] != '\\')
				j--;
			else if (i == 0)
				j--;
		}
		if ((str[i] == '$' && eq == 2) || (str[i] == '$' && eq == 0))
		{
			if (str[i + 1] && str[i + 1] == '?')
			{
				ss = ft_itoa(cnf->excode);
				while (ss[k])
				{
					ret[j] = ss[k];
					j++;
					k++;
				}
				j--;
				i++;
				free(ss);
			}
			else
			{
				j = ptenv(str, env, ++i, ret, j);
				while (str[i] && str[i] != ' ')
					i++;
				if (str[i] == '\0')
					break ;
				i--;
			}
		}
		j++;
		i++;
	}
	ret[j] = 0;
	return (ret);
}
