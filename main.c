/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/21 12:13:48 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include"./libft/libft.h"

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
	return ("");
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	*commande;
	int		fd1;
	int		fd2;
	int		i;

	if (argc < 5)
		return (1);
	if ((argc < 5) || (pipe(fd) == -1))
		return (1);
	commande = check_acsess("echo");
	if (ft_strlen(commande) == 0)
		return (1);
	i = 0;
	while (argv[i])
		i++;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[i - 1], O_RDWR | O_TRUNC);
	dup2(fd1, 0);
	dup2(fd2, 1);
	return (0);
}

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