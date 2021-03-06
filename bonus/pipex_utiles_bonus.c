/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:27:04 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 20:39:38 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*check_acces(char **envp, char *command)
{
	char	*path;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
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

int	open_file1(struct s_data *data)
{
	data->files[0] = open(data->argv[1], O_RDONLY);
	if (data->files[0] == -1 || access(data->argv[1], R_OK) == -1)
	{
		perror("Error ");
		if (access(data->argv[1], R_OK) == -1)
			return (3);
		exit(1);
	}
	return (2);
}

void	open_last_file(struct s_data *data)
{
	if (ft_strncmp(data->argv[1], "here_doc\0", 9) == 0)
		data->files[1] = open(data->argv[data->argc - 1],
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		data->files[1] = open(data->argv[data->argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(data->argv[data->argc - 1], W_OK) == -1)
	{
		perror("Error ");
		exit(1);
	}
}

int	open_files(struct s_data *data)
{
	int	i;

	if (ft_strncmp(data->argv[1], "here_doc\0", 9) == 0)
		i = here_docing(data->limiter, data->fds[1]);
	else
	{
		i = open_file1(data);
		if (i == 2)
		{
			close(data->fds[0]);
			data->fds[0] = data->files[0];
		}
	}
	open_last_file(data);
	return (i);
}
