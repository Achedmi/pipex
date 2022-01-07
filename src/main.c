/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/01/07 09:54:05 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	childing(int in, int fds[2], char *commande, char **envp)
{
	int	fk;

	fk = fork();
	if (fk == 0)
	{
		dup2(in, 0);
		dup2(fds[1], 1);
		close(fds[1]);
		close(in);
		execve(check_acces(envp, ft_split(commande, ' ')[0]),
			ft_split(commande, ' '), envp);
		write(2, ft_strjoin(commande, ": command not found \n"),
			ft_strlen(ft_strjoin(commande, ": command not found \n")));
		exit(127);
	}
	close(fds[1]);
	close(in);
}

void	exec_commande(char **argv, int fds[2], int argc, char **envp)
{
	int		in;
	int		i;
	int		fd1;

	i = 0;
	if (ft_strncmp(argv[-2], "here_doc", 8) == 0)
		fd1 = open(argv[argc - 1], O_RDWR | O_APPEND);
	else
		fd1 = open(argv[argc - 1], O_RDWR | O_TRUNC);
	if (access(argv[argc - 1], W_OK) == -1)
		perror("Error ");
	while (argv[i + 1] && access(argv[argc - 1], W_OK) == 0)
	{
		in = fds[0];
		pipe(fds);
		if (argv[i + 1] == argv[argc - 1])
			fds[1] = fd1;
		childing(in, fds, argv[i], envp);
		i++;
	}
	while (i--)
		wait(NULL);
	close(fds[0]);
	close(fd1);
}

int	here_doc_case(char *limiter, int fds[2])
{
	char	*line;

	if (pipe(fds) == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			break ;
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (3);
}

int	file_case(char *file_name, int fds[2])
{
	char	*line;
	int		file;

	if (pipe(fds) == -1)
		return (-1);
	file = open(file_name, O_RDONLY);
	if (file == -1 || access(file_name, R_OK) == -1)
	{
		perror("Error ");
		if (access(file_name, R_OK) == -1)
			return (2);
		return (-1);
	}
	while (1)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(file);
	return (2);
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	int		i;

	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		i = here_doc_case(argv[2], fds);
	else
		i = file_case(argv[1], fds);
	if (i == -1)
		return (0);
	close(fds[1]);
	exec_commande(&argv[i], fds, argc - i, envp);
	return (0);
}
