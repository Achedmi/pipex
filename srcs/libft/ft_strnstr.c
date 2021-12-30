/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:13:03 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/16 13:30:41 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_strnstr_inti(size_t *i, size_t *j, int *pos)
{
	*i = 0;
	*j = 0;
	*pos = 0;
}

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;
	int		pos;

	ft_strnstr_inti(&i, &j, &pos);
	if (ft_strlen((char *)str2) == 0 || str2 == NULL)
		return ((char *)str1);
	while (i < n && (str2[j] && str1[i]))
	{
		if ((str1[i] == str2[j]))
		{
			if (j == 0)
				pos = i;
			i++;
			j++;
			continue ;
		}
		if (j != 0)
			i = pos;
		j = 0;
		i++;
	}
	if (j == ft_strlen((char *)str2))
		return (&((char *)str1)[pos]);
	return (NULL);
}
