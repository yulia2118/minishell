/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:44:08 by fdarrin           #+#    #+#             */
/*   Updated: 2020/12/02 17:44:12 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_signal(int signal)
{
	int		pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		if (pid)
			ft_putstr_fd("\n\e[1;38;5;47mminishell:\e[0m ", 2);
	}
	if (signal == SIGQUIT)
	{
		if (!pid)
			ft_putstr_fd("Quit: 3\n", 1);
		else
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}
