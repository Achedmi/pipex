/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/01/03 11:16:15 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include"../needs/libft/libft.h"
#include"../needs/gnl/get_next_line.h"

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
	return (NULL);
}

void	execute(char **argv, int **fds, int argc)
{
	int		fd1;
	int		fk;
	int		i;
	char	*acess;

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
			free(fds[i]);
			acess = check_acsess(ft_split(argv[i], ' ')[0]);			
			execve(acess, ft_split(argv[i], ' '), NULL);
			free(acess);
		}
		wait(NULL);
		close(fds[i][0]);
		close(fds[i + 1][1]);
		free(fds[i]);
		i++;
	}
}

int	here_doc_case(char *limiter, int **fds, int argc)
{
	char	*line;
	int		j;

	if (!fds)
		return (-1);
	j = -1;
	while (++j < argc - 3)
	{
		fds[j] = malloc(2 * sizeof(int));
		if (fds[j] == NULL || pipe(fds[j]) == -1)
			return (-1);
	}
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			break ;
		write(fds[0][1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (3);
}

int	file_case(char *file_name, int **fds, int argc)
{
	char	*line;
	int		file;
	int		j;

	if (!fds)
		return (-1);
	j = -1;
	while (++j < argc - 2)
	{
		fds[j] = malloc(2 * sizeof(int));
		if (fds[j] == NULL || pipe(fds[j]) == -1)
			return (-1);
	}
	file = open(file_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		write(fds[0][1], line, ft_strlen(line));
		free(line);
	}
	close(file);
	return (2);
}

int	main(int argc, char **argv)
{
	int		**fds;
	int		i;

	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		fds = malloc((argc - 3) * sizeof(int *));
		i = here_doc_case(argv[2], fds, argc);
	}
	else
	{
		fds = malloc((argc - 2) * sizeof(int *));
		i = file_case(argv[1], fds, argc);
	}
	if (i == -1)
		return (0);
	close(fds[0][1]);
	execute(&argv[i], fds, argc - i);
	system("leaks pipex");
	return (0);
}
/*
	env variables
*/