/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_no_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:58:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/15 16:39:47 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_print(t_var *v)
{
	if (strcmp(v->first, v->last) == 0)
		ft_printf("%s", v->first);
	else
		ft_printf("%-*s", v->len, v->first);
}

void	init_len_n_last(t_var *v)
{
	int need;

	need = 0;
	v->len = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (v->len == 0)
			v->first = ft_strdup(diread->d_name);
		if (v->len == 0)
			v->last = ft_strdup(diread->d_name);
		if (v->len < ft_strlen(diread->d_name))
			v->len = ft_strlen(diread->d_name);
		if (ft_strcmp(v->last, diread->d_name) < 0)
			v->last = ft_strdup(diread->d_name);
		if ((ft_strcmp(v->first, diread->d_name) > 0) || need == 0)
		{
			if (diread->d_name[0] != '.')
				need++;
			if (diread->d_name[0] != '.')
				v->first = ft_strdup(diread->d_name);
		}
	}
	closedir(v->dir);
}

void		ascii_order(struct dirent *diread, t_var *v)
{
	ft_print(v);
	v->save = opendir(".");
	while ((diread = readdir(v->save)) != NULL)
	{
		if ((ft_strcmp(v->first, diread->d_name) < 0) && v->mid == NULL)
			v->mid = ft_strdup(diread->d_name);
		if (v->mid != NULL && (ft_strcmp(v->first, v->mid) == 0)
				&& diread->d_name[0] != '.' && (ft_strcmp(v->first, diread->d_name) < 0))
			v->mid = ft_strdup(diread->d_name);
		if ((ft_strcmp(v->first, diread->d_name) < 0)
				&& (ft_strcmp(v->mid, diread->d_name) > 0))
			v->mid = ft_strdup(diread->d_name);
	}
	closedir(v->save);
	v->first = v->mid;
}

int		ft_ls_no_flag(t_var *v)
{
	v->path = ft_strdup(".");
	init_len_n_last(v);
	v->dir = opendir(".");
	if (ft_strcmp(v->first, v->last) != 0)
		while ((diread = readdir(v->dir)) != NULL && ft_strcmp(v->first, v->last) != 0)
			ascii_order(diread, v);
	closedir(v->dir);
	ft_print(v);
	return (1);
}
