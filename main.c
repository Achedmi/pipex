/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/23 14:28:11 by achedmi          ###   ########.fr       */
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

void	execute(int i, char **argv, int *fd, int fd0)
{
	int		fd1;
	int		argv_len;
	int		fk;
	char	*args[500];
	char	str[500];
	int		l = 0;

	argv_len = 0;
	while (argv[argv_len])
		argv_len++;
	
	fd1 = open("txt7.txt", O_RDWR | O_TRUNC);
	
	
	
	puts(str);
	
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
	dup2(fd[0], 0);
	return (3);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		i;
	int		fd0;

	if ((argc < 5) || (pipe(fd) == -1))
		return (1);
	i = 1;
	if (ft_strncmp(argv[i], "here_doc", 8) == 0)
		i = here_doc(argv, fd);
	else
	{
		fd0 = open(argv[i], O_RDONLY);
		dup2(fd0, 0);
		i = 2;
	}
	execute(i, argv, fd, fd0);
	return (0);
}


	// dup2(fd[0], 0);
	// dup2(fd1, 1);
	// char *args[] = {commande, NULL};
	// while (argv[i + 1])
	// {	
	// 	if (ft_strlen(check_acsess(argv[i])) != 0)
	// 	{
	// 		free(commande);
	// 		commande = 
	// 		int fk = fork();
	// 		if (fk == 0)
	// 		{
	// 			execve(commande, args, NULL);
	// 		}
	// 		wait(NULL);
	// 		i++;			
	// 	}
	// }

	
	/*
	int fk = fork();
	if (fk == 0)
	{
		execve(commande, args, NULL);
	}*/

// int main()
// {
// 	int	fd = open("./txt.txt", O_RDWR);
// 	char *txt;
// 	while (ft_strncmp(txt, "hi", 2) != 0)
// 	{
// 		txt = get_next_line(0);
// 	}
// 	// puts(txt);
// 	return 0;
// }
// int	main(int n, char **args)
// {
// 	int	fd = open("./txt.txt", O_RDWR);
// 	int	fd3 = open("./txt3.txt", O_RDWR | O_TRUNC);
// 	char *arrs[] = {"/bin/sleep", "5", NULL};
// 	char *arrs2[] = {"/bin/echo", "kkkkk", NULL};
// 	char *arrs3[] = {"/bin/echo", "lslslsllslsllsls", NULL};

// 	dup2(fd, 0);
// 	dup2(fd3, 1);

// 	int fk = fork();
// 	if (fk == 0)
// 		execve("/bin/sleep", arrs, NULL);
// 	else
// 	{
// 		wait(NULL);
// 		int fk2 = fork();
// 		if (fk2 == 0)
// 		{
// 			close(fd3);
// 			int fd2 = open("./txt2.txt", O_RDWR | O_TRUNC);
// 			fd3 = open("./txt3.txt", O_RDWR);

// 			dup2(fd3, 0);
// 			dup2(fd2, 1);

// 			execve("/bin/echo", arrs2, NULL);
// 		}
// 		else{
// 			wait(NULL);
// 		}
// 	}
// 	return 1;
// }

//infile "ls -l" "wc -l" outfile


//	./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
//	 ./pipex here_doc LIMITER cmd cmd1 file