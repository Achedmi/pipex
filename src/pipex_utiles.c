/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achedmi <achedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:27:04 by achedmi           #+#    #+#             */
/*   Updated: 2022/01/03 20:27:21 by achedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*check_acsess(char *commande)
{
	char	*path;

	path = malloc(9 + ft_strlen(commande) + 1);
	ft_strlcat(path, "/usr/bin/", ft_strlen("/usr/bin/") + 1);
	ft_strlcat(path, commande, ft_strlen(commande) + ft_strlen(path) + 1);
	if (access(&path[4], F_OK) == 0)
		return (&path[4]);
	else if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}
