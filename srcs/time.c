/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:24:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:05:24 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	padding_all(t_var *v)
{
	struct passwd	*usr;
	struct group	*grp;

	padding_len(v);
	if ((usr = getpwuid(st.st_uid)) != NULL)
	{
		if (v->len_u < countlen(usr->pw_name))
			v->len_u = countlen(usr->pw_name);
	}
	else
	{
		if (v->len_u < nbrsize((long)st.st_uid))
			v->len_u = nbrsize((long)st.st_uid);
	}
	if ((grp = getgrgid(st.st_gid)) != NULL)
	{
		if (v->len_g < countlen(grp->gr_name))
			v->len_g = countlen(grp->gr_name);
	}
	else
	{
		if (v->len_g < nbrsize((long)st.st_gid))
			v->len_g = nbrsize((long)st.st_gid);
	}
	padding_dev(v);
}

void	algo_init_t(t_var *v)
{
	if ((st.st_mtime - v->ftime) >= 0)
	{
		if (ft_strcmp(v->first, diread->d_name) > 0
				|| (st.st_mtime - v->ftime) > 0)
		{
			free(v->first);
			v->first = ft_strdup(diread->d_name);
			v->ftime = st.st_mtime;
		}
	}
	if ((st.st_mtime - v->ltime) <= 0)
	{
		if (ft_strcmp(v->last, diread->d_name) < 0
				|| (st.st_mtime - v->ltime) < 0)
		{
			free(v->last);
			v->last = ft_strdup(diread->d_name);
			v->ltime = st.st_mtime;
		}
	}
}

void	init_print_t(t_var *v, t_flags *f)
{
	char	*name;
	char	*pathname;

	while ((diread = readdir(v->dir)) != NULL)
	{
		if (f->a == 0 && diread->d_name[0] == '.')
			continue ;
		v->len++;
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(v->path, name);
		if (lstat(pathname, &st) < 0)
			return (free_pathname(pathname, name));
		free_pathname(pathname, name);
		padding_all(v);
		if (v->first == NULL)
		{
			v->first = ft_strdup(diread->d_name);
			v->ftime = st.st_mtime;
			v->last = ft_strdup(diread->d_name);
			v->ltime = st.st_mtime;
		}
		algo_init_t(v);
	}
	closedir(v->dir);
}

void	print_ls_time(t_var *v, t_flags *f)
{
	int		i;
	char	*pathname;
	char	*name;

	i = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (f->a == 0 && diread->d_name[0] == '.')
			continue ;
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(v->path, name);
		if (lstat(pathname, &st) < 0)
			return (free_pathname(pathname, name));
		if (f->r == 1)
		{
			i = time_rev(v, i);
			free_pathname(pathname, name);
			continue ;
		}
		i = save_ascii_time(v, i, name);
		time_algo(v, i, name);
		free_pathname(pathname, name);
	}
	print_ls_time_p2(v, f);
}
