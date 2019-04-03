/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:46:37 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:12:05 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	free_n_reinitialize(t_var *v, t_flags *f)
{
	if (f->t == 0)
	{
		free(v->mid);
		if (v->last != NULL)
			free(v->last);
		free(v->first);
	}
	else
	{
		free(v->first);
		free(v->last);
	}
	v->first = NULL;
	v->last = NULL;
	v->len_u = 0;
	v->len_g = 0;
	v->len_n = 0;
	v->len_l = 0;
	v->len_s = 0;
}

void	algo_init(t_var *v, t_flags *f)
{
	char	*pathname;
	char	*name;

	if (f->a == 0 && diread->d_name[0] == '.')
		return ;
	name = ft_strdup(diread->d_name);
	pathname = ft_strjoin(v->path, name);
	if (lstat(pathname, &st) < 0)
		return (free_pathname(pathname, name));
	padding_all(v);
	if (v->first == NULL)
	{
		v->first = ft_strdup(name);
		v->last = ft_strdup(name);
	}
	if (ft_strcmp(v->first, name) > 0)
		new_alloc(v, name, 0);
	if (ft_strcmp(v->last, name) < 0)
		new_alloc(v, name, 1);
	if (v->len_n < ft_strlen(name))
		v->len_n = ft_strlen(name);
	free_pathname(pathname, name);
	v->len++;
}

void	algo_ascii_time(t_var *v, t_flags *f)
{
	if ((v->ftime - st.st_mtime) == 0)
	{
		if (f->r == 1)
		{
			ascii_time_rev(v, diread->d_name);
			return ;
		}
		if (ft_strcmp(v->first, v->mid) == 0
				&& (ft_strcmp(v->first, diread->d_name) < 0))
		{
			free(v->mid);
			v->mid = ft_strdup(diread->d_name);
		}
		if ((ft_strcmp(v->first, diread->d_name) < 0)
				&& (ft_strcmp(v->mid, diread->d_name) > 0))
		{
			free(v->mid);
			v->mid = ft_strdup(diread->d_name);
		}
	}
}
