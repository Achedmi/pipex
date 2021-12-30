/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:51:13 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/17 03:36:18 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	if (lst)
	{
		while (lst->next)
		{
			if (!f(lst->content))
			{
				del(lst);
				return (NULL);
			}
			ft_lstadd_front(&res, ft_lstnew(f(lst->content)));
			lst = lst->next;
		}
		if (!f(lst->content))
		{
			del(lst);
			return (NULL);
		}
		ft_lstadd_front(&res, ft_lstnew(f(lst->content)));
	}
	else
		res = NULL;
	return (res);
}
