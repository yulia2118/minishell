/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:04:39 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 12:08:09 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void		mess(char *p, int fd, DIR *cat)
{
	if (!p || !ft_strchr(p, '/'))
		ft_putendl_fd(": \e[1;38;5;202mcommand not found\e[0m", 2);
	else if (fd == -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mNo such file or directory\e[0m", 2);
	else if (fd == -1 && cat)
		ft_putendl_fd(": \e[1;38;5;202mis a directory\e[0m", 2);
	else if (fd > -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mPermission denied\e[0m", 2);
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
	mess(p, fd, cat);
	if ((!p || ft_strchr(p, '/') == NULL) || (fd == -1 && cat == NULL))
		status = 127;
	else
		status = 126;
	if (cat)
		closedir(cat);
	closefd(fd);
	return (status);
}

int					bin(char *p, char **targ, t_config *cnf)
{
	int status;

	status = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		if (p && ft_strchr(p, '/'))
			execve(p, targ, cnf->env);
		status = errs(p, targ[0]);
		exit(status);
	}
	else
		waitpid(g_sig.pid, &status, 0);
	if (g_sig.ctc == 1 || g_sig.cts == 1)
		return (g_sig.excode);
	status = (status == 32256 || status == 32512) ? status / 256 : !!status;
	return (status);
}
