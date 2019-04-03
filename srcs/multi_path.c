/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:45:10 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 15:02:52 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ascii_time_path(char **tab, t_var *v)
{
	char	*pathname;
	int		i;
	int		j;

	j = -1;
	while (tab[++j])
	{
		i = -1;
		pathname = ft_strjoin(v->path, tab[j]);
		if (lstat(pathname, &st) < 0)
			return (free(pathname));
		free(pathname);
		v->ftime = st.st_mtime;
		while (tab[++i])
		{
			pathname = ft_strjoin(v->path, tab[i]);
			if (lstat(pathname, &st) < 0)
				return (free(pathname));
			free(pathname);
			if ((v->ftime - st.st_mtime) == 0
					&& ft_strcmp(tab[j], tab[i]) < 0)
				algo_multi_time(tab, v, i, j);
		}
	}
}

void	time_multi_path(char **tab, t_var *v)
{
	char	*pathname;
	int		i;
	int		j;

	j = -1;
	while (tab[++j])
	{
		i = -1;
		pathname = ft_strjoin(v->path, tab[j]);
		if (lstat(pathname, &st) < 0)
			return (free(pathname));
		free(pathname);
		v->ftime = st.st_mtime;
		while (tab[++i])
		{
			pathname = ft_strjoin(v->path, tab[i]);
			if (lstat(pathname, &st) < 0)
				return (free(pathname));
			free(pathname);
			if ((v->ftime - st.st_mtime) > 0)
				algo_multi_time(tab, v, i, j);
		}
	}
	ascii_time_path(tab, v);
}

void	ascii_multi_path(char **files, t_var *v)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (files[i])
	{
		while (files[j])
		{
			if (ft_strcmp(files[i], files[j]) < 0)
			{
				tmp = files[i];
				files[i] = files[j];
				files[j] = tmp;
			}
			j++;
		}
		if (v->len_n < ft_strlen(files[i]))
			v->len_n = ft_strlen(files[i]);
		i++;
		j = 0;
	}
}

void	multi_file(t_var *v, t_flags *f)
{
	int i;

	i = 0;
	if (v->index_f != 0)
	{
		padding_file(v->files, v);
		if (f->t == 1)
			time_multi_path(v->files, v);
		else
			ascii_multi_path(v->files, v);
		if (f->r == 1)
			rev_order(v->files);
		while (v->files[i])
		{
			free(v->first);
			v->first = ft_strdup(v->files[i]);
			if (f->l == 1)
				print_long(v);
			else
				print(v);
			i++;
		}
		if (v->index_d == 0)
			free(v->first);
	}
}

void	multi_path(t_var *v, t_flags *f)
{
	int i;

	i = -1;
	multi_file(v, f);
	if (v->index_d != 0)
	{
		if (f->t == 1 && v->index_d > 2)
			time_multi_path(v->directory, v);
		else
			ascii_multi_path(v->directory, v);
		if (f->r == 1)
			rev_order(v->directory);
		while (v->directory[++i])
		{
			v->path = v->directory[i];
			f->rec == 1 ? ft_recursive_flag(v->path, f, v) :
				multi_display(v, f, i);
		}
	}
	if (f->t == 1)
		free(v->mid);
	free_multi_path(v);
}
