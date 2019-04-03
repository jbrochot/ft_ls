/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_multi_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:17:06 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 11:32:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int		countlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		nbrsize(int nb)
{
	int size;

	size = 0;
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	**free_path_stat(char *s)
{
	free(s);
	return (NULL);
}

int		free_pathname_int(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (-1);
}

void	free_pathname(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return ;
}
