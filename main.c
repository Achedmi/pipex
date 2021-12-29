/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/24 16:21:24 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include"./libft/libft.h"
#include"./get_next_line/get_next_line.h"

char	*check_acsess(char *commande)
{
	char	*path;

	path = malloc(9 + ft_strlen(commande) + 1);
	ft_strlcat(path, "/usr/bin/", ft_strlen("/usr/bin/") + 1);
	ft_strlcat(path, commande, ft_strlen(commande) + ft_strlen(path) + 1);
	if (access(&path[4], F_OK) == 0)
		return (&path[4]);
	else if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return ("");
}

void	execute(char **argv, int **fds, int argc)
{
	int		fd1;
	int		fk;
	int		i;

	i = 0;
	fd1 = open(argv[argc - 1], O_RDWR | O_TRUNC);
	while (argv[i + 1])
	{
		if (argv[i + 1] == argv[argc - 1])
			fds[i + 1][1] = fd1;
		fk = fork();
		if (fk == 0)
		{
			dup2(fds[i][0], 0);
			dup2(fds[i + 1][1], 1);
			close(fds[i][0]);
			close(fds[i + 1][1]);
			execve(check_acsess(ft_split(argv[i], ' ')[0]),
				ft_split(argv[i], ' '), NULL);
		}
		wait(NULL);
		close(fds[i][0]);
		close(fds[i + 1][1]);
		i++;
	}
}

int	here_doc_case(char *limiter, int fd)
{
	char	*tmp;

	tmp = get_next_line(0);
	while (ft_strncmp(tmp, limiter, ft_strlen(tmp) - 1) != 0)
	{
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	return (3);
}

int	file_case(char *file_name, int fd)
{
	char	*line;
	int		file;

	file = open(file_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(file);
	return (2);
}

int	main(int argc, char **argv, char **env)
{
	int		**fds;
	int		i;
	int		j;

	j = -1;
	fds = malloc(10 * sizeof(int *));
	if (fds == NULL || argc < 5)
		return (0);
	while (++j < argc - 2)
	{
		fds[j] = malloc(2 * sizeof(int));
		if (pipe(fds[j]) == -1)
			return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		i = here_doc_case(argv[2], fds[0][1]);
	else
		i = file_case(argv[1], fds[0][1]);
	close(fds[0][1]);
	execute(&argv[i], fds, argc - i);
	return (0);
}
