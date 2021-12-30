/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:16:45 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/14 10:00:00 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;

	if (!dest && !src)
		return (NULL);
	temp = dest;
	while (n--)
		*temp++ = *((unsigned char *)src++);
	return (dest);
}
