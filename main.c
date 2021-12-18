/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:12:58 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/18 16:02:39 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int	main(int n, char **args)
{
	int	fd = open("./txt.txt", O_RDWR);
	int	fd2 = open("./txt2.txt", O_RDWR);
	char *arrs[] = {"/usr/bin/grep", "ho", NULL};
	dup2(fd, 0);
	dup2(fd2, 1);
	int fk = fork();
	if (fk == 0)
		execve("/usr/bin/grep", arrs, NULL);
	else
		wait(NULL);
}
