/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:09:52 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 14:26:24 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_acces(char **envp, char *command)
{
	char	*path;
	int		i;

	i = 0;
	if (strchr(command, '/'))
		return (command);
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
	write(2, ft_strjoin(command, ": command not found \n"),
		ft_strlen(ft_strjoin(command, ": command not found \n")));
	exit(1);
}
