/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/02 18:10:05 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	childing(int in, int fds[2], char *commande, char **envp)
//{
//	int	fk;
//
//	fk = fork();
//	if (fk == 0)
//	{
//		dup2(in, 0);
//		dup2(fds[1], 1);
//		close(fds[1]);
//		close(in);
//		execve(check_acces(envp, ft_split(commande, ' ')[0]),
//			ft_split(commande, ' '), envp);
//		write(2, ft_strjoin(commande, ": command not found \n"),
//			ft_strlen(ft_strjoin(commande, ": command not found \n")));
//		exit(127);
//	}
//	close(fds[1]);
//	close(in);
// }
//
// void	exec_commande(char **argv, int fds[2], int argc, char **envp)
//{
//	int		in;
//	int		i;
//	int		fd1;
//
//	i = 0;
//	if (ft_strncmp(argv[-2], "here_doc", 8) == 0)
//		fd1 = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
//	else
//		fd1 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
//	if (access(argv[argc - 1], W_OK) == -1)
//		perror("Error ");
//	while (argv[i + 1] && access(argv[argc - 1], W_OK) == 0)
//	{
//		in = fds[0];
//		pipe(fds);
//		if (argv[i + 1] == argv[argc - 1])
//			fds[1] = fd1;
//		childing(in, fds, argv[i], envp);
//		i++;
//	}
//	while (i--)
//		wait(NULL);
//	close(fds[0]);
//	close(fd1);
// }
//
// int	here_doc_case(char *limiter, int fd)
//{
//	char	*line;
//
//	while (1)
//	{
//		line = get_next_line(0);
//		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
//			break ;
//		write(fd, line, ft_strlen(line));
//		free(line);
//	}
//	free(line);
//	return (3);
// }
//
// int	file_case(char *file_name, int fd)
//{
//	char	*line;
//	int		file;
//
//	file = open(file_name, O_RDONLY);
//	if (file == -1 || access(file_name, R_OK) == -1)
//	{
//		perror("Error ");
//		if (access(file_name, R_OK) == -1)
//			return (2);
//		return (-1);
//	}
//	while (1)
//	{
//		line = get_next_line(file);
//		if (line == NULL)
//			break ;
//		write(fd, line, ft_strlen(line));
//		free(line);
//	}
//	close(file);
//	return (2);
// }
//
// int	main(int argc, char **argv, char **envp)
//{
//	int		fds[2];
//	int		i;
//
//	if (argc != 5)
//	{
//		write(2, "wrong number of args", ft_strlen("wrong number of args"));
//		exit(1);
//	}
//	if (pipe(fds) == -1)
//		exit(1);
//	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
//		i = here_doc_case(argv[2], fds[1]);
//	else
//		i = file_case(argv[1], fds[1]);
//	if (i == -1)
//		exit(1);
//	close(fds[1]);
//	exec_commande(&argv[i], fds, argc - i, envp);
//	return (0);
// }

// int	here_doc_case(char *limiter, int fd)
// {
//     char	*line;

//     while (1)
//     {
//         line = get_next_line(0);
//         if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
//             break ;
//         write(fd, line, ft_strlen(line));
//         free(line);
//     }
//     free(line);
//     return (3);
// }

void open_files(char *file_name1, char *file_name2, int *files)
{
    files[0] = open(file_name1, O_RDONLY);
    if (files[0] == -1 || access(file_name1, R_OK) == -1)
    {
        perror("Error ");
        if (access(file_name1, R_OK) == -1)
            return;
        exit(1);
    }

    files[1] = open(file_name2, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    if (access(file_name2, W_OK) == -1)
    {
        perror("Error ");
        exit(1);
    }
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
}

void forking(int *fds, char **argv, char **envp)
{
    int id;
    int id2;
    int files[2];

    open_files(argv[1], argv[4], files);
    id = fork();
    if (id == 0)
        executing(files[0], fds[1], argv[2], envp);
    close(files[0]);
    close(fds[1]);
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

// int main(int argc, char **argv, char **envp)
// {
//     int fds[2];
//     int file;
//     int id;
//     int id2;

//     if (argc != 5)
//     {
//         write(2, "wrong number of args", ft_strlen("wrong number of args"));
//         exit(1);
//     }
//     if (pipe(fds) == -1)
//         exit(1);

//     if (!open_file(argv[1]))
//         exit(1);

//     id = fork();
//     if (id == 0)
//     {
//         dup2(file, 0);
//         dup2(fds[1], 1);
//         close(file);
//         close(fds[1]);
//         execve(check_acces(envp, ft_split(argv[2], ' ')[0]),
//                ft_split(argv[2], ' '), envp);
//         write(2, ft_strjoin(argv[2], ": command not found \n"),
//               ft_strlen(ft_strjoin(argv[2], ": command not found \n")));
//     }
//     close(file);
//     close(fds[1]);

//     file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
//     id2 = fork();
//     if (id2 == 0)
//     {
//         dup2(fds[0], 0);
//         dup2(file, 1);
//         close(fds[0]);
//         close(file);
//         execve(check_acces(envp, ft_split(argv[3], ' ')[0]),
//                ft_split(argv[3], ' '), envp);
//         write(2, ft_strjoin(argv[3], ": command not found \n"),
//               ft_strlen(ft_strjoin(argv[3], ": command not found \n")));
//     }
//     close(file);
//     close(fds[0]);
//     waitpid(id, NULL, 0);
//     waitpid(id2, NULL, 0);

//     return (0);
// }

// int main(int argc, char **argv, char **envp)
// {
//     int a;
//     int b;
//     int c;
//     int d;
//     int id;
//     argc = 1;

//     a = open("txt.txt", O_RDONLY);
//     b = open("tmp.txt", O_RDONLY);
//     c = open("tmp.txt", O_WRONLY);
//     d = open("txt8.txt", O_WRONLY);

//     id = fork();
//     if (id == 0)
//     {
//         dup2(a, 0);
//         dup2(c, 1);
//         close(a);
//         close(c);
//         execve(check_acces(envp, ft_split(argv[2], ' ')[0]),
//                ft_split(argv[2], ' '), envp);
//         write(2, ft_strjoin(argv[2], ": command not found \n"),
//               ft_strlen(ft_strjoin(argv[2], ": command not found \n")));
//     }
//     wait(NULL);
//     close(a);
//     // close(c);

//     id = fork();
//     if (id == 0)
//     {
//         dup2(b, 0);
//         dup2(d, 1);
//         close(b);
//         close(d);
//         execve(check_acces(envp, ft_split(argv[3], ' ')[0]),
//                ft_split(argv[3], ' '), envp);
//         write(2, ft_strjoin(argv[3], ": command not found \n"),
//               ft_strlen(ft_strjoin(argv[3], ": command not found \n")));
//     }
//     wait(NULL);
//     close(b);
//     close(d);
// }