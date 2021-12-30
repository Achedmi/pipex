/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:12:46 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/16 15:43:25 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*str;
	size_t	l;

	if (!s)
		return (NULL);
	str = (char *)s;
	if (len > ft_strlen(str))
		l = ft_strlen(str);
	else
		l = len;
	p = (char *)malloc((int)l + 1);
	if (p == NULL)
		return (NULL);
	if (start < ft_strlen(str))
		ft_strlcpy(p, str + start, (int)l + 1);
	else
		ft_strlcpy(p, "", 1);
	return (p);
}
