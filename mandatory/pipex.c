/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 01:31:52 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

struct s_data
{
	int files[2];
	int fds[2];
	int argc;
	char **argv;
	char **envp;
};

char *check_acces(char **envp, char *command)
{
	char *path;
	int i;

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
	write(2, ft_strjoin(command, ": command not found \n"),
		  ft_strlen(ft_strjoin(command, ": command not found \n")));
	exit(1);
}

void open_file1(struct s_data *data)
{
	data->files[0] = open(data->argv[1], O_RDONLY);
	if (data->files[0] == -1 || access(data->argv[1], R_OK) == -1)
	{
		perror("Error ");
		if (access(data->argv[1], R_OK) == -1)
			exit(1);
	}
}

void open_last_file(struct s_data *data)
{
	data->files[1] = open(data->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(data->argv[4], W_OK) == -1)
	{
		perror("Error ");
		exit(1);
	}
}

void executing(struct s_data *data, int in, int out, char *commande)
{
	dup2(in, 0);
	dup2(out, 1);
	close(data->fds[1]);
	close(data->fds[0]);
	execve(check_acces(data->envp, ft_split(commande, ' ')[0]),
		   ft_split(commande, ' '), data->envp);
	write(2, ft_strjoin(strerror(errno), "\n"), ft_strlen(ft_strjoin(strerror(errno), "\n")));
	exit(0);
}

void forking(struct s_data *data)
{
	int id;
	int id2;

	id = fork();
	if (id == 0)
	{
		open_file1(data);
		executing(data, data->files[0], data->fds[1], data->argv[2]);
	}
	id2 = fork();
	if (id2 == 0)
	{
		open_last_file(data);
		executing(data, data->fds[0], data->files[1], data->argv[3]);
	}

	close(data->fds[1]);
	close(data->fds[0]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	struct s_data *data;

	data = malloc(sizeof(struct s_data));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;

	if (argc != 5)
	{
		write(2, "wrong number of args", ft_strlen("wrong number of args"));
		exit(1);
	}
	if (pipe(data->fds) == -1)
		exit(1);
	forking(data);
}
