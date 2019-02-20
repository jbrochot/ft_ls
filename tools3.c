/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:45:34 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/20 16:26:35 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	initialize_stock_dir(t_var *v, int ac)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (v->path_long[i])
	{
		if (is_directory(v->path_long[i], v) == 1)
			j++;
		i++;
	}
	if (j > 1)
		v->file_path = 1;
	if (!(v->stock_d = (char**)malloc(sizeof(char*) * j + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i <= j)
		v->stock_d[i++] = NULL;
}

int		is_directory(char *str, t_var *v)
{
	if ((v->dir = opendir(str)) == NULL)
		return (0);
	closedir(v->dir);
	return (1);
}

char	**rev_order(char **tab)
{
	char	**tab_save;
	int		i;
	int		j;
	int		k;

	i = 1;
	j = 1;
	while (tab[i])
		i++;
	if (!(tab_save = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	k = i;
	tab_save[0] = ft_strdup(tab[0]);
	while (j < k)
	{
		tab_save[j] = ft_strdup(tab[i - 1]);
		j++;
		i--;
	}
	tab_save[j] = NULL;
	ft_strdel(tab);
	return (tab_save);
}

void	padding_multi(t_var *v, t_flags *f)
{
	int i;
	int j;

	i = 1;
	j = 1;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		while (v->path_long[j])
		{
			if (ft_strcmp(v->path_long[j], diread->d_name) != 0)
				i++;
			j++;
		}
		if (i < j)
			padding_initialisation(v, f);
		i = 1;
		j = 1;
	}
	closedir(v->dir);
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
			v->time = ft_strsub(ctime(&st.st_mtime), 4, 12);
		if (i == 0)
			v->time_l = ft_strsub(ctime(&st.st_mtime), 4, 12);
		if (ft_strcmp(ft_strsub(ctime(&st.st_mtime), 4, 12), v->time) >= 0)
		{
			v->first = diread->d_name;
			v->time = ft_strsub(ctime(&st.st_mtime), 4, 12);
		}
		if (ft_strcmp(ft_strsub(ctime(&st.st_mtime), 4, 12), v->time_l) <= 0)
		{
			v->last = diread->d_name;
			v->time_l = ft_strsub(ctime(&st.st_mtime), 4, 12);
		}
	}
	printf("\nf:%sl:%s\n", v->first, v->last);
}
