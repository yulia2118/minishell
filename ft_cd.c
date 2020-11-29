/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:41:31 by fdarrin           #+#    #+#             */
/*   Updated: 2020/11/28 20:41:34 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char		*get_env_value(char *var, char **environ)
{
	char	*key;
	char	**res;
	char	*tmp;

	if (!(key = (char *)malloc(sizeof(char) * (ft_strlen(var) + 2))))
		return (NULL);
	ft_strlcat(key, var, ft_strlen(var));
	ft_strlcat(key, "=\0", 2);
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

int			ft_cd(char **argv, char **environ)
{
	char	*home;

	if (!argv[1])
	{
		home = get_env_value("HOME", environ);
		chdir(home);
		free(home);
		return (errno);
	}
	if (chdir(argv[1]) < 0)
		ft_printf("-minishell: cd: %s: no such file or directory\n", argv[1]);
	return (errno);
}
