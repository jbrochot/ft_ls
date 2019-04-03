/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_no_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:52:59 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:14:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print(t_var *v)
{
	if (ft_strcmp(v->first, v->last) != 0)
		ft_printf("%-*s ", v->len_n, v->first);
	else
		ft_printf("%s", v->last);
}

void	rev_init_print(t_var *v)
{
	time_t	tempo;
	char	*tmp;

	tmp = ft_strdup(v->first);
	free(v->first);
	v->first = ft_strdup(v->last);
	free(v->last);
	v->last = ft_strdup(tmp);
	free(tmp);
	tempo = v->ftime;
	v->ftime = v->ltime;
	v->ltime = tempo;
}

void	new_alloc(t_var *v, char *name, int mod)
{
	if (mod == 0)
	{
		free(v->first);
		v->first = ft_strdup(name);
	}
	if (mod == 1)
	{
		free(v->last);
		v->last = ft_strdup(name);
	}
	if (mod == 2)
	{
		free(v->mid);
		v->mid = ft_strdup(name);
	}
}

void	init_print(t_var *v, t_flags *f)
{
	v->len = 0;
	v->len_n = 0;
	v->dir = opendir(v->path);
	if (v->dir == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(ft_dirchr(v->path, '/'), 2);
		perror(" ");
		ft_putchar_fd('\n', 2);
		return ;
	}
	if (f->t == 0)
	{
		while ((diread = readdir(v->dir)) != NULL)
			algo_init(v, f);
		closedir(v->dir);
	}
	else
		init_print_t(v, f);
	if (f->r == 1)
		rev_init_print(v);
}

int		print_ls(t_var *v, t_flags *f)
{
	init_print(v, f);
	if (f->l == 1 && v->len > 0 && v->is_dev == 0)
		ft_printf("total %d\n", ft_count_blocks(v, f));
	else if (f->l == 1 && v->len > 0 && v->is_dev == 1)
		ft_printf("total %d\n", 0);
	while (v->len > 0)
	{
		if (f->l == 1)
			print_long(v);
		else
			print(v);
		if (f->t == 1 && ft_strcmp(v->first, v->last) != 0)
			print_ls_time(v, f);
		else if (ft_strcmp(v->first, v->last) != 0)
			print_ls_ascii(v, f);
		v->len--;
	}
	free_n_reinitialize(v, f);
	return (0);
}
