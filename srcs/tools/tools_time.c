/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:37:50 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/02 15:36:35 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	time_algo_rev(t_var *v)
{
	if ((v->mtime - st.st_mtime) == 0
			&& ft_strcmp(v->mid, diread->d_name) < 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(diread->d_name);
	}
	else if ((v->mtime - st.st_mtime) > 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(diread->d_name);
	}
}

int		time_rev(t_var *v, int i)
{
	if ((v->ftime - st.st_mtime) == 0
			&& ft_strcmp(v->first, diread->d_name) > 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(diread->d_name);
		i++;
	}
	if (((v->ftime - st.st_mtime)) < 0 && v->mtime == 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(diread->d_name);
	}
	if ((v->ftime - v->mtime) == 0
			&& (v->ftime - st.st_mtime) < 0 && i == 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(diread->d_name);
	}
	if ((v->ftime - st.st_mtime) < 0
			&& (v->mtime - st.st_mtime) >= 0 && i == 0)
		time_algo_rev(v);
	return (i);
}

int		save_ascii_time(t_var *v, int i, char *name)
{
	if ((v->ftime - st.st_mtime) == 0
			&& ft_strcmp(v->first, name) < 0)
	{
		if (v->mid != NULL)
			free(v->mid);
		v->mtime = st.st_mtime;
		v->mid = ft_strdup(name);
		i++;
	}
	return (i);
}

void	time_algo2(t_var *v, char *name)
{
	if ((v->mtime - st.st_mtime) == 0
				&& ft_strcmp(v->mid, name) > 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(name);
	}
	else if ((v->mtime - st.st_mtime) < 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(name);
	}
}

void	time_algo(t_var *v, int i, char *name)
{
	if (((v->ftime - st.st_mtime)) > 0 && v->mtime == 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(name);
	}
	if ((v->ftime - v->mtime) == 0
			&& (v->ftime - st.st_mtime) > 0 && i == 0)
	{
		v->mtime = st.st_mtime;
		free(v->mid);
		v->mid = ft_strdup(name);
	}
	if ((v->ftime - st.st_mtime) > 0
			&& (v->mtime - st.st_mtime) <= 0 && i == 0)
		time_algo2(v, name);
}
