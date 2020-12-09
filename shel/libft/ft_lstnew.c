/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:24:51 by wsallei           #+#    #+#             */
/*   Updated: 2020/05/11 17:05:35 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		list->content = NULL;
	else
	{
		if (!(list->content = malloc(sizeof(*content))))
			return (NULL);
		list->content = content;
	}
	list->next = NULL;
	return (list);
}
