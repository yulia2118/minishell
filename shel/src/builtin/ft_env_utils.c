/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:25 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/18 15:22:32 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		change_env(t_env *current_env, t_env *env)
{
	if (current_env->value && env->value == NULL)
		free(env->value);
	else
	{
		free(current_env->value);
		current_env->value = env->value;
	}
	free(env->key);
	free(env);
}

void		sort_env(t_list *first_elem, t_list *second_elem, t_list *temp_elem)
{
	void	*temp_content;

	if (temp_elem)
		first_elem->next->next = temp_elem;
	temp_content = first_elem->content;
	first_elem->content = second_elem->content;
	second_elem->content = temp_content;
}

t_env		*init_env(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}

void		add_env(t_list *env_list, t_env *env)
{
	int		cmp;
	t_list	*temp_elem;
	t_env	*current_env;

	while (env_list)
	{
		current_env = (t_env*)env_list->content;
		cmp = compare_str(env->key, current_env->key);
		if (cmp <= 0 || env_list->next == NULL)
		{
			if (cmp < 0)
			{
				temp_elem = env_list->next;
				env_list->next = ft_lstnew(env);
				sort_env(env_list, env_list->next, temp_elem);
			}
			else if (cmp == 0)
				change_env(current_env, env);
			else
				env_list->next = ft_lstnew(env);
			break ;
		}
		env_list = env_list->next;
	}
}
