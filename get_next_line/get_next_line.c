/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 04:08:40 by achedmi           #+#    #+#             */
/*   Updated: 2021/12/21 14:21:03 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	has_next_line(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			if (str[i] == '\n')
				return (i + 1);
	}
	return (0);
}

char	*crop(char *s)
{
	char	*p;
	int		i;

	i = 0;
	if (has_next_line(s))
		p = malloc(has_next_line(s) + 1);
	else
		p = malloc(ft_strlen(s));
	if (p == NULL)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		if (s[i] == '\n')
		{	
			p[i + 1] = '\0';
			return (p);
		}
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*search_for_next(char *tmp_line, int fd)
{
	int			l;
	char		*tmp_line_address;
	char		*tmp_of_tmp;

	tmp_of_tmp = malloc(1 + 1);
	if (!tmp_of_tmp)
		return (NULL);
	while (!has_next_line(tmp_line))
	{
		l = read(fd, tmp_of_tmp, 1);
		if (l <= 0)
			break ;
		tmp_of_tmp[l] = '\0';
		tmp_line_address = tmp_line;
		tmp_line = ft_strjoin(tmp_line, tmp_of_tmp);
		free(tmp_line_address);
	}
	free(tmp_of_tmp);
	return (tmp_line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*tmp_line;

	if (fd < 0 || 1 <= 0)
		return (NULL);
	tmp_line = ft_calloc(1 + 1, 1);
	if (!tmp_line)
		return (NULL);
	if (rest != NULL)
	{
		free(tmp_line);
		tmp_line = ft_strjoin(rest, "");
		free(rest);
	}
	tmp_line = search_for_next(tmp_line, fd);
	line = crop(tmp_line);
	if (has_next_line(tmp_line))
		rest = ft_strjoin(&tmp_line[has_next_line(tmp_line)], "");
	else
		rest = NULL;
	if (!*line)
		return (free(tmp_line), free(line), NULL);
	return (free(tmp_line), line);
}
