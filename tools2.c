/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:34:54 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/21 15:01:06 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		count_lenf(int nb)
{
	int count;

	count = 0;
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

void	init_rev(t_var *v, t_flags *f)
{
	char *s;

	if (f->r == 1)
	{
		s = ft_strdup(v->first);
		v->first = ft_strdup(v->last);
		v->last = ft_strdup(s);
		free(s);
	}
}

void	init_last(t_var *v, int ac)
{
	int j;

	j = -1;
	while (++j < ac)
		if (is_directory(v->path_long[j], v) == 0 && v->path_long[j][0] != '-')
			v->last = v->path_long[j];
	j = -1;
	while (++j < ac)
		if (v->len < ft_strlen(v->path_long[j]))
			v->len = ft_strlen(v->path_long[j]);
	padding_multi(v);
}

void	ascii_init(t_var *v, int ac)
{
	int		i;
	int		j;
	char	*tmp;

	j = 1;
	i = 1;
	while (j < ac)
	{
		while (i < ac)
		{
			if (ft_strcmp(v->path_long[j], v->path_long[i]) < 0)
			{
				tmp = v->path_long[j];
				v->path_long[j] = v->path_long[i];
				v->path_long[i] = tmp;
			}
			if (v->len < ft_strlen(v->path_long[i]))
				v->len = ft_strlen(v->path_long[i]);
			i++;
		}
		j++;
		i = 1;
	}
	init_last(v, ac);
}

void	ascii_rev(t_var *v)
{
	static int i;

	if ((ft_strcmp(v->first, diread->d_name) > 0) && i == 0)
	{
		i++;
		v->mid = ft_strdup(diread->d_name);
	}
	if (ft_strcmp(v->first, v->mid) == 0
		&& (ft_strcmp(v->first, diread->d_name) > 0))
		v->mid = ft_strdup(diread->d_name);
	if ((ft_strcmp(v->first, diread->d_name) > 0)
		&& (ft_strcmp(v->mid, diread->d_name) < 0))
		v->mid = ft_strdup(diread->d_name);
}
