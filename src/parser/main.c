/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:58:36 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/16 19:58:38 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_sig	g_sig;

static	void	con(t_config *cnf, int x)
{
	if (x < 0)
	{
		ft_putstr_fd("\e[1;38;5;202merror: read line try again\e[0m\n", 2);
		cnf->excode = 127;
		return ;
	}
	else if (x == 0)
	{
		tf(cnf->env);
		cnf->senvl = freeenv(cnf->senvl);
		freeenvl(cnf->envl);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

static	int		chprs(char *line, t_config *cnf)
{
	if (close_quote(line))
	{
		ft_putstr_fd("minishell: syntax error: not close quote\n", 2);
		cnf->excode = 127;
		free(line);
		return (1);
	}
	if (cherrdir(line, cnf))
	{
		free(line);
		return (1);
	}
	if (checkunexp(cnf, line))
	{
		free(line);
		return (1);
	}
	return (0);
}

void			pars(t_config *cnf)
{
	char	*line;
	int		x;

	signal(SIGINT, ft_signalc);
	signal(SIGQUIT, ft_signals);
	ft_putstr_fd("\e[1;38;5;47mminishell:\e[0m ", 2);
	line = NULL;
	if ((x = get_next_line(2, &line)) <= 0)
		con(cnf, x);
	cnf->excode = (g_sig.ctc == 1) ? g_sig.excode : cnf->excode;
	if (line)
	{
		if (chprs(line, cnf))
			return ;
		cnf->tok = analys(line);
	}
	else
		free(line);
}

int				main(int argc, char **argv, char **env)
{
	t_config cnf;

	argc = 0;
	if (argv && argv[0])
		argv[0][0] = argc;
	init(&cnf, env);
	cnf.excode = 0;
	while (cnf.exit)
	{
		g_sig.ctc = 0;
		g_sig.pid = 0;
		g_sig.excode = 0;
		g_sig.cts = 0;
		cnf.tok = NULL;
		pars(&cnf);
		if (cnf.tok != NULL)
			exec(&cnf);
		freetok(cnf.tok);
	}
	tf(cnf.env);
	freeenvl(cnf.envl);
	cnf.senvl = freeenv(cnf.senvl);
	write(1, "\0", 0);
	return (cnf.excode);
}
