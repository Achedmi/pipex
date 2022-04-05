/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 02:14:22 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <errno.h>

// void childing(int in, int fds[2], char *commande, char **envp)
// {
// 	int fk;

// 	fk = fork();
// 	if (fk == 0)
// 	{
// 		dup2(in, 0);
// 		dup2(fds[1], 1);
// 		close(fds[1]);
// 		close(in);
// 		execve(check_acces(envp, ft_split(commande, ' ')[0]),
// 			   ft_split(commande, ' '), envp);
// 		write(2, ft_strjoin(commande, ": command not found \n"),
// 			  ft_strlen(ft_strjoin(commande, ": command not found \n")));
// 		exit(127);
// 	}
// 	close(fds[1]);
// 	close(in);
// }

// void exec_commande(char **argv, int fds[2], int argc, char **envp)
// {
// 	int in;
// 	int i;
// 	int fd1;

// 	i = 0;
// 	if (ft_strncmp(argv[-2], "here_doc", 8) == 0)
// 		fd1 = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
// 	else
// 		fd1 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
// 	if (access(argv[argc - 1], W_OK) == -1)
// 		perror("Error ");
// 	while (argv[i + 1] && access(argv[argc - 1], W_OK) == 0)
// 	{
// 		in = fds[0];
// 		pipe(fds);
// 		if (argv[i + 1] == argv[argc - 1])
// 			fds[1] = fd1;
// 		childing(in, fds, argv[i], envp);
// 		i++;
// 	}
// 	while (i--)
// 		wait(NULL);
// 	close(fds[0]);
// 	close(fd1);
// }

// int here_doc_case(char *limiter, int fd)
// {
// 	char *line;

// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
// 			break;
// 		write(fd, line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(line);
// 	return (3);
// }

// int file_case(char *file_name, int fd)
// {
// 	char *line;
// 	int file;

// 	file = open(file_name, O_RDONLY);
// 	if (file == -1 || access(file_name, R_OK) == -1)
// 	{
// 		perror("Error ");
// 		if (access(file_name, R_OK) == -1)
// 			return (2);
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(file);
// 		if (line == NULL)
// 			break;
// 		write(fd, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(file);
// 	return (2);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	int fds[2];
// 	int i;

// 	if (argc < 5)
// 	{
// 		write(2, "wrong number of args", ft_strlen("wrong number of args"));
// 		exit(1);
// 	}
// 	if (pipe(fds) == -1)
// 		return (-1);
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		i = here_doc_case(argv[2], fds[1]);
// 	else
// 		i = file_case(argv[1], fds[1]);
// 	if (i == -1)
// 		return (0);
// 	close(fds[1]);
// 	exec_commande(&argv[i], fds, argc - i, envp);
// 	return (0);
// }

struct s_data
{
	int files[2];
	int fds[2];
	int argc;
	char **argv;
	char **envp;
	int *id;
};

int here_docing(char *limiter, int fd)
{
	char *line;

	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			break;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (3);
}

int open_file1(struct s_data *data)
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

void open_last_file(struct s_data *data)
{
	if (ft_strncmp(data->argv[1], "here_doc", 8) == 0)
		data->files[1] = open(data->argv[data->argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		data->files[1] = open(data->argv[data->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(data->argv[data->argc - 1], W_OK) == -1)
	{
		perror("Error ");
		exit(1);
	}
}

int open_files(struct s_data *data)
{
	int i;

	if (ft_strncmp(data->argv[1], "here_doc", 8) == 0)
	{
		i = here_docing(data->argv[2], data->fds[1]);
		// data->files[0] = data->fds[0];
	}
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

void executing(struct s_data *data, int in, char *commande)
{
	dup2(in, 0);
	dup2(data->fds[1], 1);
	close(data->fds[0]);
	close(data->fds[1]);
	close(in);
	execve(check_acces(data->envp, ft_split(commande, ' ')[0]),
		   ft_split(commande, ' '), data->envp);
	// write(2, ft_strjoin(commande, ": command not found \n"),
	// 	  ft_strlen(ft_strjoin(commande, ": command not found \n")));
	write(2, ft_strjoin(strerror(errno), "\n"), ft_strlen(ft_strjoin(strerror(errno), "\n")));

	exit(0);
}

void to_execute(struct s_data *data, int *i, int *j, int *tmp_in)
{
	if (*i == data->argc - 2)
		data->fds[1] = data->files[1];
	if (*i < data->argc - 2)
		if (pipe(data->fds) == -1)
			exit(1);
	data->id[*j] = fork();
	if (data->id[(*j)++] == 0)
		executing(data, *tmp_in, data->argv[(*i)]);
	close(*tmp_in);
	close(data->fds[1]);
	*tmp_in = data->fds[0];
	(*i)++;
}

void forking(struct s_data *data)
{
	int i;
	int j;
	int tmp_in;

	i = open_files(data);
	data->id = malloc(sizeof(int) * (data->argc - (i + 1)));
	// tmp_in = data->files[0];
	tmp_in = data->fds[0];
	j = 0;
	close(data->fds[1]);
	while (data->argv[i + 1])
		to_execute(data, &i, &j, &tmp_in);
	while (j--)
		waitpid(data->id[j], NULL, 0);
	free(data->id);
}

int main(int argc, char **argv, char **envp)
{
	struct s_data *data;

	data = malloc(sizeof(struct s_data));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;

	if (argc < 5)
	{
		write(2, "wrong number of args", ft_strlen("wrong number of args"));
		exit(1);
	}
	if (pipe(data->fds) == -1)
		exit(1);
	forking(data);
}

// handle commande path :/usr/bin/awk