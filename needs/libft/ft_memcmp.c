/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:48:34 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/12 08:40:56 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t				c;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	c = 0;
	ptr1 = (const unsigned char *)str1;
	ptr2 = (const unsigned char *)str2;
	if ((ptr1 == ptr2) || n == 0)
		return (0);
	while ((c + 1 < n) && (ptr1[c] == ptr2[c]))
		c ++;
	return (ptr1[c] - ptr2[c]);
}
