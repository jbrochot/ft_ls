/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:22:14 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/21 16:53:41 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int		ft_count_names(char *strpath, t_flags *flag)
{
	DIR				*dir;
	struct dirent	*diread;
	int				count;

	count = 0;
	dir = opendir(strpath);
	while ((diread = readdir(dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

static void		ft_stock_names(char *strpath, char **stock, t_flags *flag)
{
	DIR				*dir;
	struct dirent	*diread;
	int				i;

	i = 0;
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
		stock[i] = ft_strdup(diread->d_name);
		i++;
	}
	stock[i] = NULL;
	closedir(dir);
}

void			ft_recursive_flag(char *str, t_flags *flag, t_var *v)
{
	struct stat		st;
	char			**stock;
	int				name_count;
	int				i;

	i = 0;
	v->path = str;
	name_count = ft_count_names(v->path, flag);
	if (!(stock = (char**)malloc(sizeof(char*) * name_count + 1)))
		return ;
	ft_stock_names(v->path, stock, flag);
	flag->R = 0;
//	ft_printf("%s:\n", v->path);
	ft_putstr(v->path);
	ft_putstr(":\n");
	ft_display(flag, v);
	ft_putstr("\n\n");
//	ft_printf("\n\n");
	while (stock[i])
	{
//		ft_init_path(v, str, stock[i]);
		if (stat(ft_strjoin(str, stock[i]), &st) < 0)
			return ;
		if (S_ISDIR(st.st_mode))
			ft_recursive_flag(ft_strjoin(str, ft_strjoin(stock[i], "/")), flag, v);
//		free(stock[i]);
		i++;
	}
}
