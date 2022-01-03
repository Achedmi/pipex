/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:17:40 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/15 15:08:23 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;
	char	*str;

	str = (char *)s;
	l = ft_strlen(str);
	if (str[l] == '\0' && (char)c == '\0')
	{
		return (&str[l]);
	}
	while (l--)
	{		
		if (str[l] == (char)c)
			return (str + l);
	}
	return (NULL);
}
