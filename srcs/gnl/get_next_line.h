/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:10:01 by achedmi           #+#    #+#             */
/*   Updated: 2021/11/29 15:27:55 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<unistd.h>
# include<stdlib.h>

int		has_next_line(char *str);
char	*crop(char *s);
char	*search_for_next(char *tmp_line, int fd);
char	*get_next_line(int fd);
#endif
