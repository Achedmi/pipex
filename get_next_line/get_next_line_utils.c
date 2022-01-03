/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 04:07:53 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/29 01:39:00 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(const char *s)
{		
	size_t	c;

	c = 0;
	while (*s)
	{
		s++;
		c++;
	}
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	p = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	c;
	size_t	n;

	c = 0;
	n = count * size;
	p = malloc(n);
	if (p == NULL)
		return (NULL);
	while (c < n)
	{
		((unsigned char *)p)[c] = 0;
		c ++;
	}
	return (p);
}
