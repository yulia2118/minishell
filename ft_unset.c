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

void		remove_env(char *argv, t_config *cnf)
{
	char	**new_env;
	int		env_len;
	int		remove;
	int		i;

	env_len = ft_strlen2(cnf->env);
	if (!(new_env = (char **)malloc(sizeof(char *) * env_len)))
		exit(0);
	new_env[env_len - 1] = NULL;
	i = 0;
	remove = 0;
	while (cnf->env[i])
	{
		if (!ft_strncmp(cnf->env[i], argv, ft_strlen(argv)))
		{
			free(cnf->env[i]);
			remove = 1;
		}
		else
			new_env[i - remove] = cnf->env[i];
		i++;
	}
	free(cnf->env);
	cnf->env = new_env;
}

int			env_exist(char *argv, t_config *cnf)
{
	int	i;

	i = 0;
	while (cnf->env[i++])
	{
		if (!ft_strncmp(cnf->env[i], argv, ft_strlen(argv)))
			return (1);
	}
	return (0);
}

int			ft_unset(char **argv, t_config *cnf)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (env_exist(argv[i], cnf))
			remove_env(argv[i], cnf);
	}
	return (errno);
}
