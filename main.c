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

void	execute(int i, char **argv, int fds[10][2], int argc)
{
	int		fd1;
	int		fk;

	fd1 = open(argv[argc - 1], O_RDWR | O_TRUNC);
	while (argv[i + 1])
	{
		if (argv[i + 1] == argv[argc - 1])
			fds[i - 1][1] = fd1;
		fk = fork();
		if (fk == 0)
		{
			dup2(fds[i - 2][0], 0);
			dup2(fds[i - 1][1], 1);
			close(fds[i - 2][0]);
			close(fds[i - 1][1]);
			execve(check_acsess(ft_split(argv[i], ' ')[0]),
				ft_split(argv[i], ' '), NULL);
		}
		wait(NULL);
		close(fds[i - 2][0]);
		close(fds[i - 1][1]);
		i++;
	}
}

int	here_doc(char **argv, int *fd)
{
	char	*tmp;

	tmp = get_next_line(0);
	while (ft_strncmp(tmp, argv[2], ft_strlen(tmp) - 1) != 0)
	{
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	return (3);
}

int	main(int argc, char **argv, char **env)
{
	int		fds[10][2];
	int		i;
	int		txt;
	char	*line;
	char	*tmp;

	pipe(fds[0]);
	pipe(fds[1]);
	pipe(fds[2]);
	pipe(fds[3]);
	pipe(fds[4]);
	pipe(fds[5]);
	pipe(fds[6]);
	if ((argc < 4))
		return (1);
	// if ((argc < 4) || (pipe(fd) == -1))
	// 	return (1);
	i = 1;
	if (ft_strncmp(argv[i], "here_doc", 8) == 0)
		i = here_doc(argv, fds[0]);
	else
	{
		txt = open(argv[i], O_RDONLY);
		while (1)
		{
			line = get_next_line(txt);
			if(line == NULL)
				break;
			write(fds[0][1], line, ft_strlen(line));
		}
		i = 2;
		close(txt);
	}
	close(fds[0][1]);
	execute(i, argv, fds, argc);
	return (0);
}

// ./a.out txt.txt ls wc txt7.txt


//	./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
//	 ./pipex here_doc LIMITER cmd cmd1 file