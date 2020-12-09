/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:09:25 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/27 16:09:29 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tif(int **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	tf(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		countargs(t_arg *arg)
{
	t_arg	*tmp;
	int		i;

	if (!arg)
		return (0);
	i = 0;
	tmp = arg;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int		lenenv(t_env *env)
{
	t_env	*tmp;
	int		i;

	if (!env)
		return (0);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_env	*freeenv(t_env *env)
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
	return (env);
}
