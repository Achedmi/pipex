/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:06:04 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/12 09:57:40 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, ft_strlen((char *)s1) + 1);
	ft_strlcpy(p + ft_strlen(p), s2, ft_strlen((char *)s2) + 1);
	return (p);
}
