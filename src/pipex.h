/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:22:37 by achedmi           #+#    #+#             */
/*   Updated: 2022/01/03 20:27:33 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<stdio.h>
# include<fcntl.h>
# include<unistd.h>
# include<sys/wait.h>
# include"../needs/libft/libft.h"
# include"../needs/gnl/get_next_line.h"

char	*check_acces(char **envp, char *command);
void	execute(char **argv, int fds[2], int argc);
int		here_doc_case(char *limiter, int fds[2]);
int		ile_case(char *file_name, int fds[2], int argc);
#endif