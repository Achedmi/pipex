/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:47:56 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/14 11:54:49 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	size_t	j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while ((ft_strchr(set, s1[i]) != NULL) && s1[i])
		i++;
	j = ft_strlen(&((char *)s1)[i]);
	while ((ft_strchr(set, s1[i + j]) != NULL) && j)
		j--;
	res = ft_substr(&s1[i], 0, j + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[i], j + 2);
	return (res);
}
