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

// void	execute(int i, char **argv, int *fd, int fd0)
// {
// 	int		fd1;
// 	int		argv_len;
// 	int		fk;
// 	char	*args[500];

// 	argv_len = 0;
// 	while (argv[argv_len])
// 		argv_len++;

// 	fd1 = open("txt7.txt", O_RDWR | O_TRUNC);
	
// 	fk = fork();
// 	if(fk == 0)
// 	{
// 		dup2(fd[1], 1);
// 		close(fd[1]);

// 		args[0] = argv[i];
// 		args[1] = NULL;		
// 		execve(check_acsess(argv[i]), args, NULL);
// 	}	
// 	wait(NULL);
// 	i++;
	
// 	close(fd0);

// 	fk = fork();
// 	if(fk == 0)
// 	{
		
// 		dup2(fd[0], 0);
// 		dup2(fd[1], 1);
		
// 		close(fd[0]);
// 		close(fd[1]);
		
// 		args[0] = argv[i];
// 		args[1] = NULL;				
// 		execve(check_acsess(argv[i]), args, NULL);
// 	}	
// 	wait(NULL);
// 	i++;

// 	close(fd[1]);

// 	// puts(argv[i]);
	
// 	fk = fork();
// 	if(fk == 0)
// 	{
// 		dup2(fd1, 1);
// 		dup2(fd[0], 0);
		
// 		close(fd[0]);
// 		close(fd1);
		
// 		args[0] = argv[i];
// 		args[1] = NULL;
		
// 		execve(check_acsess(argv[i]), args, NULL);
// 	}	
// 	wait(NULL);
	
// 	close(fd1);
// 	close(fd[0]);
// 	close(fd[1]);
// 	i++;
	
// }

void	execute(int i, char **argv, int *fd, int argc)
{
	int	fd1;
	int fk;
	char *args[5];
	char *line;

	fd1 =  open(argv[argc - 1], O_RDWR | O_TRUNC);
	while(argv[i])
	{
		if(argv[i] == argv[argc - 2])
		{
			close(fd[1]);
			fd[1] = fd1;
		}
		else
		{

			close(fd[0]);
			close(fd[1]);
			pipe(fd);
		}
		fk = fork();
		if(fk == 0)
		{
			dup2(fd[0], 0);
			dup2(fd[1], 1);

			close(fd[0]);
			close(fd[1]);

			args[0] = argv[i];
			args[1] = NULL;
			execve(check_acsess(argv[i]), args, NULL);
		}
		wait(NULL);
		i++;
	}

	close(fd[0]);
	close(fd[1]);
	close(fd1);
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
	int		fd[2];
	int		i;
	int		txt;
	char	*line;
	char	*tmp;

	if ((argc < 4) || (pipe(fd) == -1))
		return (1);
	i = 1;
	if (ft_strncmp(argv[i], "here_doc", 8) == 0)
		i = here_doc(argv, fd);
	else
	{
		txt = open(argv[i], O_RDONLY);
		while (1)
		{
			line = get_next_line(txt);
			if(line == NULL)
				break;
			write(fd[1], line, ft_strlen(line));
		}
		i = 2;
		close(txt);
	}
	execute(i, argv, fd, argc);
	return (0);
}

// ./a.out txt.txt ls wc txt7.txt


//	./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
//	 ./pipex here_doc LIMITER cmd cmd1 file