/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:17:01 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/20 11:36:54 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			counter;

	counter = -1;
	while (++counter < n)
		((unsigned char *)str)[counter] = (unsigned char)c;
	return (str);
}
