/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scratch <scratch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:21:53 by achedmi           #+#    #+#             */
/*   Updated: 2022/03/12 18:58:06 by scratch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		if ((res > 2147483647 && sign == 1)
			|| (res > 2147483648 && sign == -1) || ft_isdigit(str[i]) == 0)
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		i++;
	}
	return (res * sign);
}
