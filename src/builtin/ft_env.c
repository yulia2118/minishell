/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:25 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/18 15:22:32 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		freelistenv(t_list *env_list)
{
	t_env	*tenv;
	t_list	*tlist;

	while (env_list)
	{
		tlist = env_list;
		tenv = (t_env*)env_list->content;
		free(tenv->key);
		free(tenv->value);
		free(tenv);
		env_list = env_list->next;
		free(tlist);
	}
}

void		addtoenvl(t_config *cnf, char **key_value)
{
	t_env	*tenv;
	t_env	*add;

	if (key_value && key_value[0] && key_value[1])
	{
		add = malloc(sizeof(t_env));
		add->key = ft_strdup(key_value[0]);
		add->value = ft_strdup(key_value[1]);
		add->next = NULL;
		tenv = cnf->envl;
		while (tenv->next)
			tenv = tenv->next;
		tenv->next = add;
	}
}

int			ft_env(char **environ)
{
	while (*environ)
	{
		write(1, *environ, ft_strlen(*environ));
		write(1, "\n", 1);
		environ++;
	}
	return (errno);
}
