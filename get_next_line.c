/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:01:16 by fdarrin           #+#    #+#             */
/*   Updated: 2020/07/24 18:17:37 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		result(int bytes, char *nptr)
{
	if (bytes == -1)
		return (-1);
	if (nptr)
		return (1);
	return (0);
}

void	copy_tail(char **tail, char **nptr)
{
	char	*temp;

	**nptr = '\0';
	temp = *tail;
	*tail = ft_strdup(++*nptr);
	free(temp);
}

void	check_tail(char ***line, char **tail, char **nptr)
{
	char	*temp;

	if ((*nptr = ft_strchr(*tail, '\n')))
	{
		**nptr = '\0';
		temp = **line;
		**line = ft_strjoin(**line, *tail);
		free(temp);
		temp = *tail;
		*tail = ft_strdup(++*nptr);
		free(temp);
	}
	else
	{
		temp = **line;
		**line = ft_strjoin(**line, *tail);
		free(temp);
		temp = *tail;
		*tail = NULL;
		free(temp);
	}
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				bytes;
	static char		*tail;
	char			*temp;
	char			*nptr;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || !(*line = malloc(1)))
		return (-1);
	**line = 0;
	nptr = NULL;
	bytes = 0;
	if (tail)
		check_tail(&line, &tail, &nptr);
	while (!nptr && (bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if ((nptr = ft_strchr(buf, '\n')))
		{
			copy_tail(&tail, &nptr);
		}
		temp = *line;
		*line = ft_strjoin(*line, buf);
		free(temp);
	}
	return (result(bytes, nptr));
}
