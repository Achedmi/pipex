/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:50:54 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/17 01:32:31 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		if (ft_lstsize(lst[0]) > 0)
		{
			ft_lstlast(*lst)->next = new;
		}
		else
			ft_lstadd_front(lst, new);
	}
}
