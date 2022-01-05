/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:27:04 by achedmi           #+#    #+#             */
/*   Updated: 2022/01/03 20:27:21 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*check_acsess(char **envp, char *command)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = &envp[i][5];
			i = -1;
			while (ft_split(path, ':')[++i])
			{
				if (access(ft_strjoin(ft_strjoin(ft_split(path, ':')[i],
							"/"), command), F_OK) == 0)
					return (ft_strjoin(ft_strjoin(ft_split(path, ':')[i],
							"/"), command));
			}
			break ;
		}
	}
	return (NULL);
}
