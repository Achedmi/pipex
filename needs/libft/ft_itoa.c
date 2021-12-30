/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 07:59:10 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/16 20:21:26 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	itoa_count(int temp)
{
	int	c;

	c = 1;
	while (temp / 10 != 0)
	{
		c++;
		temp = temp / 10;
	}
	return (c);
}

char	*itoainsert(int c, char *res, int sign, int n)
{
	while (c--)
	{
		res[c] = (sign * n) % 10 + '0';
		n = n / 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		c;
	int		sign;

	c = itoa_count(n);
	sign = 1;
	if (n < 0)
	{
		c++;
		if (n <= -2147483648)
		{
			res = ft_strdup("-2147483648");
			return (res);
		}
		sign = -1;
	}
	res = (char *)malloc(c + 1);
	if (!res)
		return (NULL);
	res[c] = '\0';
	res = itoainsert(c, res, sign, n);
	return (res);
}
