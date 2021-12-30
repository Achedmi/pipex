/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:43:31 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/12 08:45:53 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*temp;

	temp = dst;
	if (dst == NULL && src == NULL && n > 0)
		return (NULL);
	if (temp < (unsigned char *)src)
		while (n--)
			*temp++ = *((unsigned char *)src++);
	else
		while (n--)
			temp[n] = ((unsigned char *)src)[n];
	return (dst);
}
