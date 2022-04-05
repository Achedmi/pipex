/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 20:37:33 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_docing(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (3);
}

void	executing(struct s_data *data, int in, char *commande)
{
	dup2(in, 0);
	dup2(data->fds[1], 1);
	close(data->fds[0]);
	close(data->fds[1]);
	close(in);
	execve(check_acces(data->envp, ft_split(commande, ' ')[0]),
		ft_split(commande, ' '), data->envp);
	write(2, ft_strjoin(strerror(errno), "\n"),
		ft_strlen(ft_strjoin(strerror(errno), "\n")));
	exit(0);
}

void	to_execute(struct s_data *data, int *i, int *j, int *tmp_in)
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

void	forking(struct s_data *data)
{
	int	i;
	int	j;
	int	tmp_in;

	i = open_files(data);
	data->id = malloc(sizeof(int) * (data->argc - (i + 1)));
	tmp_in = data->fds[0];
	j = 0;
	close(data->fds[1]);
	while (data->argv[i + 1])
		to_execute(data, &i, &j, &tmp_in);
	while (j--)
		waitpid(data->id[j], NULL, 0);
	free(data->id);
}

int	main(int argc, char **argv, char **envp)
{
	struct s_data	*data;

	data = malloc(sizeof(struct s_data));
	data->argc = argc;
	data->argv = argv;
	data->limiter = ft_strjoin(argv[2], "\n");
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
