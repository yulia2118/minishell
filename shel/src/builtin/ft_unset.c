/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:41:14 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/25 22:41:20 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		free_env(void *argv)
{
	t_env	*env;

	env = (t_env*)argv;
	free(env->value);
	free(env->key);
	free(env);
}

void		remove_env(t_list *env_list, t_list *prev_element)
{
	t_list *tmp_elem;

	free_env(env_list->content);
	if (prev_element)
	{
		prev_element->next = env_list->next;
		free(env_list);
	}
	else if (env_list->next)
	{
		tmp_elem = env_list->next;
		env_list->content = env_list->next->content;
		env_list->next = env_list->next->next;
		free(tmp_elem);
	}
}

int			ft_unset(char **argv, char **environ)
{
	t_list	*env_list;
	t_list	*prev_element;
	t_env	*current_env;

	env_list = list_from_environ(environ);
	while (*argv)
	{
		prev_element = NULL;
		while (env_list)
		{
			current_env = (t_env*)env_list->content;
			if (!compare_str(current_env->key, *argv))
			{
				remove_env(env_list, prev_element);
				return (errno);
			}
			prev_element = env_list;
			env_list = env_list->next;
		}
		argv++;
	}
	return (errno);
}