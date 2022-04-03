/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/03 03:00:31 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_acces(char **envp, char *command)
{
	char *path;
	int i;

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
												 "/"),
									  command),
						   F_OK) == 0)
					return (ft_strjoin(ft_strjoin(ft_split(path, ':')[i],
												  "/"),
									   command));
			}
			break;
		}
	}
	return (NULL);
}

int open_file1(char *file_name, int *files)
{
	files[0] = open(file_name, O_RDONLY);
	if (files[0] == -1 || access(file_name, R_OK) == -1)
	{
		perror("Error ");
		if (access(file_name, R_OK) == -1)
			return (2);
		exit(1);
	}
	return (2);
}

void open_last_file(char *file_name, int *files)
{
	files[1] = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(file_name, W_OK) == -1)
	{
		perror("Error ");
		exit(1);
	}
}

void open_files(char **argv, int *files)
{
	open_file1(argv[1], files);
	open_last_file(argv[4], files);
}

void executing(int in, int out, char *commande, char **envp)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	execve(check_acces(envp, ft_split(commande, ' ')[0]),
		   ft_split(commande, ' '), envp);
	write(2, ft_strjoin(commande, ": command not found \n"),
		  ft_strlen(ft_strjoin(commande, ": command not found \n")));
	exit(0);
}

void forking(int *fds, char **argv, char **envp)
{
	int id;
	int id2;
	int files[2];

	open_files(argv, files);
	id = fork();
	if (id == 0)
		executing(files[0], fds[1], argv[2], envp);
	close(fds[1]);
	close(files[0]);
	id2 = fork();
	if (id2 == 0)
		executing(fds[0], files[1], argv[3], envp);
	close(fds[0]);
	close(files[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	int fds[2];

	if (argc != 5)
	{
		write(2, "wrong number of args", ft_strlen("wrong number of args"));
		exit(1);
	}
	if (pipe(fds) == -1)
		exit(1);
	forking(fds, argv, envp);
}