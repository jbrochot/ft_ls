/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:25:55 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/03 10:35:00 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		ft_count_names(char *strpath, t_flags *flag, t_var *v)
{
	DIR				*dir;
	char			*name;
	char			*pathname;

	v->counter = 0;
	dir = opendir(strpath);
	if (dir == NULL)
	{
		ft_usage(v, strpath, 2);
		return (-1);
	}
	while ((diread = readdir(dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(strpath, name);
		if (lstat(pathname, &st) < 0)
			return (free_pathname_int(pathname, name));
		free_pathname(pathname, name);
		if (S_ISDIR(st.st_mode))
			v->counter++;
	}
	closedir(dir);
	return (v->counter);
}

static void		ft_stock_names(char *strpath, char **stock, t_flags *flag)
{
	DIR		*dir;
	char	*pathname;
	char	*name;

	dir = opendir(strpath);
	while ((diread = readdir(dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		else if (flag->a == 1)
		{
			if (diread->d_name[0] == '.'
					&& (diread->d_name[1] == '.' || diread->d_name[1] == '\0'))
				continue ;
		}
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(strpath, name);
		if (lstat(pathname, &st) < 0)
			return (free_pathname(pathname, name));
		free_pathname(pathname, name);
		if (S_ISDIR(st.st_mode))
			*stock++ = ft_strdup(diread->d_name);
	}
	closedir(dir);
	*stock = NULL;
}

static char		*ft_init_new_path(char *str, char *stock, int mod)
{
	char	*new;
	char	*tmp;

	if (mod == 1)
	{
		if (!(new = ft_strjoin(str, stock)))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strjoin(stock, "/")))
			return (NULL);
		if (!(new = ft_strjoin(str, tmp)))
			return (NULL);
		free(tmp);
	}
	return (new);
}

static void		ft_recursive_p2(char *str, char **stock, t_flags *f, t_var *v)
{
	int		i;
	char	*recursive_path;

	i = 0;
	while (stock[i])
	{
		v->path = ft_init_new_path(str, stock[i], 1);
		if (lstat(v->path, &st) < 0)
		{
			free(v->path);
			while (stock[i])
				free(stock[i++]);
			free(stock);
			return ;
		}
		free(v->path);
		if (S_ISDIR(st.st_mode))
		{
			recursive_path = ft_init_new_path(str, stock[i], 2);
			ft_recursive_flag(recursive_path, f, v);
			free(recursive_path);
		}
		free(stock[i++]);
	}
	free(stock);
}

void			ft_recursive_flag(char *str, t_flags *flag, t_var *v)
{
	char	**stock;
	int		name_count;
	int		i;

	i = 0;
	v->path = str;
	name_count = ft_count_names(v->path, flag, v);
	if (name_count == -1)
		return ;
	if (!(stock = (char**)malloc(sizeof(char*) * (name_count + 1))))
		return ;
	ft_stock_names(v->path, stock, flag);
	if (flag->t == 1)
		time_multi_path(stock, v);
	else
		ascii_multi_path(stock, v);
	if (flag->r == 1)
		rev_order(stock);
	if (v->index_d > 0 && v->index_f > 0)
		ft_printf("\n");
	ft_printf("%s:\n", v->path);
	print_ls(v, flag);
	ft_printf((flag->l == 0) ? "\n\n" : "\n");
	ft_recursive_p2(str, stock, flag, v);
}
