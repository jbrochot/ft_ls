/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:48:57 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:16:06 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	ft_display_time(char *time)
{
	char	*time2;
	char	*time3;

	if (ft_strcmp(time, "2019") == 0 || ft_strcmp(time, "2018") == 0)
	{
		free(time);
		time = ft_strsub(ctime(&st.st_mtime), 4, 12);
		ft_printf(" %s ", time);
	}
	else
	{
		free(time);
		time2 = ft_strsub(ctime(&st.st_mtime), 19, 5);
		time3 = ft_strsub(ctime(&st.st_mtime), 4, 7);
		time = ft_strjoin(time3, time2);
		ft_printf(" %s ", time);
		free(time2);
		free(time3);
	}
	free(time);
}

void	padding_len(t_var *v)
{
	if (v->len_l < nbrsize(st.st_nlink))
		v->len_l = nbrsize(st.st_nlink);
	if (v->len_s < nbrsize(st.st_size))
		v->len_s = nbrsize(st.st_size);
}

void	print_ls_time_p2(t_var *v, t_flags *f)
{
	closedir(v->dir);
	if ((v->ftime - v->mtime) == 0)
		ascii_time(v, f);
	free(v->first);
	v->first = ft_strdup(v->mid);
	v->ftime = v->mtime;
}

void	ascii_time_rev(t_var *v, char *s)
{
	if (ft_strcmp(v->first, v->mid) == 0
			&& (ft_strcmp(v->first, s) > 0))
	{
		free(v->mid);
		v->mid = ft_strdup(s);
	}
	if ((ft_strcmp(v->first, s) > 0)
			&& (ft_strcmp(v->mid, s) < 0))
	{
		free(v->mid);
		v->mid = ft_strdup(s);
	}
}

void	ascii_time(t_var *v, t_flags *f)
{
	char	*name;
	char	*pathname;

	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (diread->d_name[0] == '.' && f->a == 0)
			continue ;
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(v->path, name);
		if (lstat(pathname, &st))
			return (free_pathname(pathname, name));
		free_pathname(pathname, name);
		algo_ascii_time(v, f);
	}
	closedir(v->dir);
	free(v->first);
	v->first = ft_strdup(v->mid);
}
