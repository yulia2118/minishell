/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:34:56 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/18 18:35:01 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			compare_str(const char *s1, const char *s2)
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

int			ft_strlen2(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
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

void		print_export(t_list *env_list)
{
	t_env	env;

	while (env_list)
	{
		env = *(t_env*)env_list->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env.key, 1);
		if (env.value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env.value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			write(1, "\n", 1);
		env_list = env_list->next;
	}
}

t_list		*get_sorted_list(t_list *env_list)
{
	t_list	*temp_content;
	t_list	*sorted_list;
	t_env	*first_elem;
	t_env	*second_elem;
	int		size;

	sorted_list = env_list;
	size = ft_lstsize(env_list);
	while (size--)
	{
		env_list = sorted_list;
		while (env_list->next)
		{
			first_elem = (t_env*)env_list->content;
			second_elem = (t_env*)env_list->next->content;
			if (compare_str(first_elem->key, second_elem->key) > 0)
			{
				temp_content = env_list->content;
				env_list->content = env_list->next->content;
				env_list->next->content = temp_content;
			}
			env_list = env_list->next;
		}
	}
	return (sorted_list);
}

t_list		*list_from_environ(char **environ)
{
	t_env	*env;
	t_list	*env_list;
	int		i;

	env_list = NULL;
	while (*environ)
	{
		if (!(env = (t_env*)malloc(sizeof(t_env))))
			return (NULL);
		i = ft_strchr(*environ, '=') - *environ;
		env->key = ft_substr(*environ, 0, i);
		env->value = ft_substr(*environ, i + 1, ft_strlen(*environ) - i - 1);
		ft_lstadd_back(&env_list, ft_lstnew(env));
		environ++;
	}
	env_list = get_sorted_list(env_list);
	return (env_list);
}

int			ft_export(int argc, char **argv, char **environ)
{
	t_list	*env_list;
	char	**key_value;

	env_list = list_from_environ(environ);
	if (argc == 1)
		print_export(env_list);
	else
	{
		while (*argv)
		{
			key_value = ft_split(*argv, '=');
			if (ft_strlen2(key_value) == 1)
			{
				if (ft_strchr(*argv, '='))
					key_value[1] = ft_strdup("\0");
			}
			add_env(env_list, init_env(key_value));
			free(key_value);
			argv++;
		}
	}
	return (errno);
}

int			main(int argc, char **argv, char **environ)
{
	int		res;

	res = ft_export(argc, argv, environ);
	return (res);
}
