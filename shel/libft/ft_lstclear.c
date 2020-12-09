/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 23:13:14 by fdarrin           #+#    #+#             */
/*   Updated: 2020/05/29 14:51:10 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;

	if (lst && del)
	{
		while (*lst != NULL)
		{
			elem = *lst;
			*lst = elem->next;
			del(elem->content);
			free(elem);
		}
	}
}
