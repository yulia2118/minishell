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

#include "minishell.h"

int		compare_str(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void		free_env(void *argv)
{
	t_env	*env;

	env = (t_env*)argv;
	free(env->value);
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

void		add_env(t_list *env_list, t_env *env)
{
	int		cmp;
	t_list	*temp_elem;
	t_env	*current_env;

	while (env_list)
	{
		current_env = env_list->content;
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

t_env		*init_env(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}

t_list		*list_from_environ(char **environ)
{
	char	**key_value;
	t_env	*env;
	t_list	*env_list;

	env_list = NULL;
	while (*environ)
	{
		key_value = ft_split(*environ, '=');
		env = init_env(key_value);
		free(key_value[2]);
		free(key_value);
		if (!env_list)
			env_list = ft_lstnew(env);
		else
			add_env(env_list, env);
		environ++;
	}
	return (env_list);
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

int			ft_unset(char **argv, t_list *env_list)
{
	t_list	*prev_element;
	t_env	*current_env;

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

int			main(int argc, char **argv, char **environ)
{
	t_list	*env_list;
	int		res;

	env_list = list_from_environ(environ);
	ft_unset(argv, env_list);
	return (res);
}
