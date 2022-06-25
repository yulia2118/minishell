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

static	int		newline(char *tail, int bytes)
{
	int i;

	i = 0;
	if (bytes == 0 && tail && tail[0] == '\0')
		return (-1);
	if (bytes == 0 || tail == NULL)
		return (0);
	while (tail[i])
	{
		if (tail[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static	char	*concat(char *tail)
{
	int		i;
	char	*line;

	i = 0;
	while (tail && tail[i] && tail[i] != '\n')
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
	{
		free(tail);
		return (NULL);
	}
	i = 0;
	while (tail && tail[i] && tail[i] != '\n')
	{
		line[i] = tail[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

static	void	put(char *ret, char *tail, char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tail && tail[i])
		ret[i++] = tail[j++];
	j = 0;
	while (buf[j])
	{
		ret[i] = buf[j];
		j++;
		i++;
	}
	ret[i] = '\0';
}

static	char	*joinbuf(char *tail, char *buf)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (tail && tail[i])
		i++;
	while (buf[j])
		j++;
	if (!(ret = malloc(sizeof(char) * (i + j + 1))))
	{
		if (tail)
			free(tail);
		return (NULL);
	}
	put(ret, tail, buf);
	if (tail)
		free(tail);
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				bytes;
	static char		*tail;

	tail = NULL;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	bytes = 1;
	while (!(newline(tail, bytes)))
	{
		if ((bytes = read(fd, buf, BUFFER_SIZE)) < 0)
			return (-1);
		buf[bytes] = '\0';
		if (!(tail = joinbuf(tail, buf)))
			return (-1);
	}
	if (newline(tail, bytes) == -1 && (*line = tail))
	{
		free(tail);
		return (0);
	}
	if (!(*line = concat(tail)))
		return (-1);
	free(tail);
	return (bytes == 0 ? 0 : 1);
}
