/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 09:47:18 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/26 13:03:32 by jebrocho         ###   ########.fr       */
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
			if (ft_strcmp(diread->d_name, v->first) != 0
					&& ft_strcmp(ft_strjoin(diread->d_name,
					ft_strchr(v->first, '/')), v->first) != 0)
				continue ;
			if (stat(ft_strjoin(v->path, v->first), &st) < 0)
				return ;
			if (lstat(ft_strjoin(v->path, v->first), &st) < 0)
				return ;
			ft_display_type(v);
			ft_display_rights();
			ft_printf("  %*d", v->len_link, st.st_nlink);
			ft_display_usr_grp();
			ft_printf("  %*d", v->len_file, st.st_size);
			ft_printf(" %.24s ", ft_strsub(ctime(&st.st_mtime), 4, 12));
			ft_print(v, flag);
		}
		closedir(v->dir);
	}
	else
		ft_print(v, flag);
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
	init_len_n_last(v, flag);
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (diread->d_name[0] == '.' && flag->a == 0)
			continue ;
		if (flag->t == 1)
			time_order(v, flag);
		else
			ascii_order(v, flag);
	}
	closedir(v->dir);
}

void		ft_display(t_flags *flag, t_var *v)
{
	if (v->file_path == 1)
	{
		display_multi(v, flag);
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
