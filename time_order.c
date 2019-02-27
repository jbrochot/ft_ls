/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:41:52 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/27 16:32:06 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		cmp_time(time_t s1, time_t s2)
{
	return (s1 - s2);
}

void	ascii_time_rev(t_var *v, char *s)
{
	if (ft_strcmp(v->first, v->mid) == 0
			&& (ft_strcmp(v->first, s) > 0))
		v->mid = ft_strdup(s);
	if ((ft_strcmp(v->first, s) > 0)
			&& (ft_strcmp(v->mid, s) < 0))
		v->mid = ft_strdup(s);
}

void	ascii_time(t_var *v, t_flags *f)
{
	v->save = opendir(v->path);
	while ((diread = readdir(v->save)) != NULL)
	{
		if (diread->d_name[0] == '.' && f->a == 0)
			continue ;
		if (stat(ft_strjoin(v->path, diread->d_name), &st))
			return ;
		if (cmp_time(v->time, st.st_mtime) == 0)
		{
			if (f->r == 1)
			{
				ascii_time_rev(v, diread->d_name);
				continue ;
			}
			if (ft_strcmp(v->first, v->mid) == 0
					&& (ft_strcmp(v->first, diread->d_name) < 0))
			{
				v->time_m = st.st_mtime;
				v->mid = ft_strdup(diread->d_name);
			}
			if ((ft_strcmp(v->first, diread->d_name) < 0)
					&& (ft_strcmp(v->mid, diread->d_name) > 0))
			{
				v->time_m = st.st_mtime;
				v->mid = ft_strdup(diread->d_name);
			}
		}
	}
	v->time = v->time_m;
	v->first = v->mid;
	closedir(v->save);
}

int		time_rev(t_var *v, int i)
{
	if (cmp_time(v->time, st.st_mtime) == 0
				&& ft_strcmp(v->first, diread->d_name) > 0)
	{
			v->time_m = st.st_mtime;
			v->mid = ft_strdup(diread->d_name);
			i++;
	}
	if ((cmp_time(v->time, st.st_mtime)) < 0 && v->time_m == 0)
	{
		v->time_m = st.st_mtime;
		v->mid = ft_strdup(diread->d_name);
	}
	if (cmp_time(v->time, v->time_m) == 0
			&& cmp_time(v->time, st.st_mtime) < 0 && i == 0)
	{
		v->time_m = st.st_mtime;
		v->mid = ft_strdup(diread->d_name);
	}
	if (cmp_time(v->time, st.st_mtime) < 0
			&& cmp_time(v->time_m, st.st_mtime) >= 0 && i == 0)
	{
		if (cmp_time(v->time_m, st.st_mtime) == 0
				&& ft_strcmp(v->mid, diread->d_name) < 0)
		{
			v->time_m = st.st_mtime;
			v->mid = ft_strdup(diread->d_name);
		}
		else if (cmp_time(v->time_m, st.st_mtime) > 0)
		{
			v->time_m = st.st_mtime;
			v->mid = ft_strdup(diread->d_name);
		}
	}
	return (i);
}

void	time_order(t_var *v, t_flags *f)
{
	int i;

	i = 0;
	ft_print(v, f);
	v->save = opendir(v->path);
	while ((diread = readdir(v->save)) != NULL)
	{
		if (diread->d_name[0] == '.' && f->a == 0)
			continue ;
		if (stat(ft_strjoin(v->path, diread->d_name), &st) < 0)
			return ;
		if (f->r == 1)
		{
			i = time_rev(v, i);
			continue ;
		}
		if (cmp_time(v->time, st.st_mtime) == 0
				&& ft_strcmp(v->first, diread->d_name) < 0)
		{
			v->time_m = st.st_mtime;
			v->mid = ft_strdup(diread->d_name);
			i++;
		}
		if ((cmp_time(v->time, st.st_mtime)) > 0 && v->time_m == 0)
		{
			v->time_m = st.st_mtime;
			v->mid = ft_strdup(diread->d_name);
		}
		if (cmp_time(v->time, v->time_m) == 0
				&& cmp_time(v->time, st.st_mtime) > 0 && i == 0)
		{
				v->time_m = st.st_mtime;
				v->mid = ft_strdup(diread->d_name);
		}
		if (cmp_time(v->time, st.st_mtime) > 0
				&& cmp_time(v->time_m, st.st_mtime) <= 0 && i == 0)
		{
			if (cmp_time(v->time_m, st.st_mtime) == 0
					&& ft_strcmp(v->mid, diread->d_name) > 0)
			{
				v->time_m = st.st_mtime;
				v->mid = ft_strdup(diread->d_name);
			}
			else if (cmp_time(v->time_m, st.st_mtime) < 0)
			{
				v->time_m = st.st_mtime;
				v->mid = ft_strdup(diread->d_name);
			}
		}
	}
	closedir(v->save);
	if (cmp_time(v->time, v->time_m) == 0)
		ascii_time(v, f);
	v->first = v->mid;
	v->time = v->time_m;
}

void	init_flag_t(t_var *v, t_flags *f)
{
	int i;

	i = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (f->a == 0 && diread->d_name[0] == '.')
			continue ;
		if (stat(ft_strjoin(v->path, diread->d_name), &st) < 0)
			return ;
		if (i == 0)
		{
			v->first = ft_strdup(diread->d_name);
			v->time = st.st_mtime;
		}
		if (i == 0)
		{
			v->last = ft_strdup(diread->d_name);
			v->time_l = st.st_mtime;
		}
		if (cmp_time(st.st_mtime, v->time) >= 0)
		{
			if (ft_strcmp(v->first, diread->d_name) > 0
					|| cmp_time(st.st_mtime, v->time) > 0)
			{
				v->first = ft_strdup(diread->d_name);
				v->time = st.st_mtime;
			}
			
		}
		if (cmp_time(st.st_mtime, v->time_l) <= 0)
		{
			if (ft_strcmp(v->last, diread->d_name) < 0
					|| cmp_time(st.st_mtime, v->time_l) < 0)
			{
				v->last = ft_strdup(diread->d_name);
				v->time_l = st.st_mtime;
			}
		}
		i++;
	}
	closedir(v->dir);
	if (f->r == 1)
	{
		v->time_m = v->time;
		v->time = v->time_l;
		v->time_l = v->time_m;
		v->time_m = 0;
		v->mid = ft_strdup(v->first);
		v->first = ft_strdup(v->last);
		v->last = ft_strdup(v->mid);
		v->mid = NULL;
	}
}
