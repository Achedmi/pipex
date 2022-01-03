/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:10:01 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/21 14:57:32 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<unistd.h>
# include<stdlib.h>

void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
int		has_next_line(char *str);
char	*crop(char *s);
char	*search_for_next(char *tmp_line, int fd);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
#endif