/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:59:07 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/12 10:02:06 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	srclen;

	srclen = ft_strlen((char *)src);
	if (n > 0)
	{	
		if (srclen >= n)
		{
			ft_memmove(dst, src, n - 1);
			dst[n - 1] = '\0';
		}
		else
		{
			ft_memmove(dst, src, srclen);
			dst[srclen] = '\0';
		}
	}
	else
		return (srclen);
	return (srclen);
}
