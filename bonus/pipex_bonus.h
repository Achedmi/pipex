/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:22:37 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 20:15:02 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../needs/libft/libft.h"
#include "../needs/gnl/get_next_line.h"
#include <errno.h>

struct s_data
{
	int files[2];
	int fds[2];
	int argc;
	char **argv;
	char **envp;
	int *id;
	char *limiter;
};
char *check_acces(char **envp, char *command);
int open_file1(struct s_data *data);
void open_last_file(struct s_data *data);
int open_files(struct s_data *data);
int here_docing(char *limiter, int fd);

#endif