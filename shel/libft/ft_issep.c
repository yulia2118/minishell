/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:59:41 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/08 19:59:44 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int			ft_srt(char *s1, char *set)
{
	size_t	i;
	size_t	f;
	int		count;

	count = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		f = 0;
		while (set[f] != '\0')
		{
			if (s1[i] == set[f])
				count++;
			f++;
		}
		i++;
	}
	return (count);
}

static	char		*ft_trim(char *s1, char *set, char *rez)
{
	size_t	i;
	size_t	f;
	size_t	count;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		f = 0;
		while (set[f] != '\0')
		{
			if (s1[i] == set[f])
			{
				i++;
				continue;
			}
			f++;
		}
		rez[count] = s1[i];
		count++;
		i++;
	}
	rez[count] = '\0';
	return (rez);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*rez;

	if (!s1 || !set)
		return (NULL);
	size = (ft_strlen((char *)s1) - ft_srt((char *)s1, (char *)set));
	if (!(rez = malloc(sizeof(*rez) * (size + 1))))
		return (NULL);
	return (ft_trim((char *)s1, (char *)set, rez));
}
