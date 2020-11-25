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

int		ft_strlen2(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	change_env(t_env *current_env, t_env *env)
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

void	sort_env(t_list *first_element, t_list *second_element,
						  t_list *temp_elem)
{
	void	*temp_content;

	if (temp_elem)
		first_element->next->next = temp_elem;
	temp_content = first_element->content;
	first_element->content = second_element->content;
	second_element->content = temp_content;
}

void	add_env(t_list *env_list, t_env *env)
{
	t_list	*temp_elem;
	t_env	*current_env;
	int		compare_result;

	while (env_list)
	{
		current_env = env_list->content;
		compare_result = strcmp(env->key, current_env->key);
		if (compare_result <= 0 || env_list->next == NULL)
		{
			if (compare_result < 0)
			{
				temp_elem = env_list->next;
				env_list->next = ft_lstnew(env);
				sort_env(env_list, env_list->next, temp_elem);
			}
			else if (compare_result == 0)
				change_env(current_env, env);
			else
				env_list->next = ft_lstnew(env);
			break ;
		}
		env_list = env_list->next;
	}
}

t_env	*init_env(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}

t_list	*list_from_environ(char **environ)
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

void	print_export(t_list *env_list)
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

void	ft_export(int argc, char **argv, char **environ)
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
}

int		main(int argc, char **argv, char **environ)
{
	ft_export(argc, argv, environ);
	return (0);
}
