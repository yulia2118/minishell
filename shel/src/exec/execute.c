/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:55:00 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/29 23:55:02 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char		*srchpth(char *pb, char *func)
{
	DIR				*cat;
	struct dirent	*rec;
	char			*allp;
	char			*tmp;

	allp = NULL;
	if (!(cat = opendir(pb)))
		return (NULL);
	while ((rec = readdir(cat)) != NULL)
	{
		if (!(ft_strcmp(rec->d_name, func)))
		{
			tmp = ft_strjoin(pb, "/");
			allp = ft_strjoin(tmp, rec->d_name);
			free(tmp);
		}
	}
	closedir(cat);
	return (allp);
}

static	int			errs(char *p, char *func)
{
	int fd;
	int status;
	DIR	*cat;

	status = 0;
	cat = 0;
	fd = -1;
	if (p)
	{
		fd = open(p, O_WRONLY);
		cat = opendir(p);
	}
	ft_putstr_fd(func, 2);
	if (!p || !ft_strchr(p, '/'))
		ft_putendl_fd(": \e[1;38;5;202mcommand not found\e[0m", 2);
	else if (fd == -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mNo such file or directory\e[0m", 2);
	else if (fd == -1 && cat)
		ft_putendl_fd(": \e[1;38;5;202mis a directory\e[0m", 2);
	else if (fd > -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mPermission denied\e[0m", 2);
	if ((!p || ft_strchr(p, '/') == NULL) || (fd == -1 && cat == NULL))
		status = 127;
	else
		status = 126;
	if (cat)
		closedir(cat);
	closefd(fd);
	return (status);
}

static	int			bin(char *p, char **targ, t_config *cnf, t_tok *pnt)
{
	int status;

	status = 0;
	cnf->pid = fork();
	if (cnf->pid == 0)
	{
		if (p && ft_strchr(p, '/'))
			execve(p, targ, cnf->env);
		status = errs(p, targ[0]);
		exit(status);
	}
	else
		waitpid(cnf->pid, &status, 0);
	status = (status == 32256 || status == 32512) ? status / 256 : !!status;
	return (status);
}

static int			is_absolute_path(char *path)
{
	struct stat	s;

	if (!(stat(path, &s)))
		return (1);
	return (0);
}

int					goexec(t_config *cnf, t_tok *pnt, char **targ)
{
	int		status;
	int		i;
	char	*p;
	char	**tp;
	t_env	*env;

	i = 0;
	p = NULL;
	env = cnf->envl;
	status = 127;
	while (env && env->key && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if (env != NULL)
	{
		tp = ft_split(env->value, ':');
		if (!(pnt->func) && !tp[0])
			return (1);
		while (pnt->func && tp[i] && p == NULL)
			p = srchpth(tp[i++], pnt->func);
	}
	if (is_absolute_path(targ[0]) && !p)
		status = bin(targ[0], targ, cnf, pnt);
	if (p != NULL)
		status = bin(p, targ, cnf, pnt);
	else
		status = bin(p, targ, cnf, pnt);
	free(p);
	tf(tp);
	return (status);
}
