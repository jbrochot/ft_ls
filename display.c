/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 09:47:18 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/15 16:40:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		ft_print_file_path(t_flags *flag, t_var *v)
{
	if (flag->l == 1)
	{
		v->dir = opendir(v->path);
		while ((diread = readdir(v->dir)) != NULL)
		{
			if (ft_strcmp(diread->d_name, v->path_end) != 0)
				continue ;
			if (stat(ft_strjoin(v->path, diread->d_name), &st) < 0)
				return ;
			ft_display_type(st);
			ft_display_rights(st);
			ft_printf("  %3d", st.st_nlink);
			ft_display_usr_grp(st);
			ft_printf("  %5d", st.st_size);
			ft_printf(" %.24s ", ft_strsub(ctime(&st.st_mtime), 4, 12));
			ft_print_name(*diread, v);
		}
		closedir(v->dir);
	}
	else
		ft_printf("%s%s\n", v->path, v->path_end);
}

void		ft_print_name(struct dirent diread, t_var *v)
{
	if (v->file_path == 1)
	{
		ft_printf("%s%s\n", v->path, v->path_end);
		return ;
	}
	if (ft_strcmp(diread.d_name, v->last) == 0)
		ft_printf("%s ", diread.d_name);
	else
		ft_printf("%-*s ", v->len, diread.d_name);
}

void		ft_display_std(t_flags *flag, t_var *v)
{
	v->len = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (v->len < ft_strlen(diread->d_name))
			v->len = ft_strlen(diread->d_name);
		v->last = ft_strdup(diread->d_name);
	}
	closedir(v->dir);
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (diread->d_name[0] == '.' && flag->a == 0)
			continue ;
		ft_print_name(*diread, v);
	}
	closedir(v->dir);
}
/*
int			ft_ls_no_flag(t_var *v)
{
	v->len = 0;
	v->dir = opendir(".");
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (v->len < ft_strlen(diread->d_name))
			v->len = ft_strlen(diread->d_name);
		v->last = ft_strdup(diread->d_name);
	}
	closedir(v->dir);
	v->dir = opendir(".");
	while ((diread = readdir(v->dir)) != NULL)
		if (diread->d_name[0] != '.')
			ft_print_name(*diread, v);
	closedir(v->dir);
	return (1);
}*/

void		ft_display(t_flags *flag, t_var *v)
{
	if (v->file_path == 1)
	{
		ft_print_file_path(flag, v);
		return ;
	}
	if (flag->R == 1)
		ft_recursive_flag(v->path, flag, v);
	else
	{
		if (flag->l == 0)
			ft_display_std(flag, v);
		else
			ft_display_long(flag, v);
	}
}
