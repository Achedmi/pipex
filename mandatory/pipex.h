/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:22:37 by achedmi           #+#    #+#             */
/*   Updated: 2022/04/05 20:40:45 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<fcntl.h>
# include<unistd.h>
# include<sys/wait.h>
# include"../needs/libft/libft.h"
# include"../needs/gnl/get_next_line.h"
# include <errno.h>

char	*check_acces(char **envp, char *command);
#endif