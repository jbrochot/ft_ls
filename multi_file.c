/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:38:20 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/19 18:00:39 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	stock_dir(char *str, t_var *v)
{
	static int i;

	v->stock_d[i] = ft_strdup(str);
	i++;
	v->stock_d[i] = NULL;
}

void	print_multi_file(char *path, t_var *v, t_flags *f)
{
	ft_printf("%s:\n", path);
	v->path = ft_strjoin(path, "/");
	if (f->l == 0)
		ft_display_std(f, v);
	else
		ft_display_long(f, v);
}

void	display_multi(t_var *v, t_flags *f)
{
	int i;

	i = 0;
	while (v->path_long[i + 1])
	{
		i++;
		if (is_directory(v->path_long[i], v) == 1)
		{
			stock_dir(v->path_long[i], v);
			continue ;
		}
		if (v->path_long[i][0] != '-')
		{
			v->first = v->path_long[i];
			v->path = "./";
			ft_print_file_path(f, v);
		}
	}
	i = 0;
	while (v->stock_d[i])
	{
		if (v->stock_d[i + 1] == NULL)
			v->c_dir = 0;
		print_multi_file(v->stock_d[i++], v, f);
	}
}
