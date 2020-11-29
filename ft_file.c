/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:43:31 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/28 20:43:34 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char			*get_env_value(char *var, char **environ)
{
	char		*key;
	char		**res;
	char		*tmp;

	if (!(key = (char *)malloc(sizeof(char) * (ft_strlen(var) + 2))))
		return (NULL);
	ft_strlcat(key, var, ft_strlen(var));
	ft_strlcat(key, "=/0", 2);
	while (*environ)
	{
		if (!ft_strncmp(*environ, key, ft_strlen(key)))
		{
			res = ft_split(*environ, '=');
			tmp = ft_strjoin(res[1], "");
			free_array(res);
			free(key);
			return (tmp);
		}
		environ++;
	}
	free(key);
	return (NULL);
}

static int		is_absolute_path(char *path)
{
	struct stat	s;

	if (!(stat(path, &s)))
		return (1);
	return (0);
}

char			*get_path(char *cmd, char **environ)
{
	char		*file_name;
	struct stat	buf;
	char		**paths;
	char		*tmp;
	int			i;

	if (is_absolute_path(cmd))
		return (cmd);
	tmp = get_env_value("PATH", environ);
	paths = ft_split(tmp, ':');
	i = 0;
	while (paths[i++])
	{
		tmp = ft_strjoin("/", cmd);
		file_name = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(file_name, &buf) == 0)
		{
			free_array(paths);
			return (file_name);
		}
		free(file_name);
	}
	free_array(paths);
	return (NULL);
}

int				ft_file(char *cmd, char **argv, char **environ)
{
	int			res;
	char		*file;

	file = get_path(cmd, environ);
	res = execve(file, argv, environ);
	if (res < 0)
		printf("-minishell: %s: command not found\n", cmd);
	return (errno);
}
