/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:15:36 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:29:00 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			malloc_path(t_var *v)
{
	if (!(v->files = (char**)malloc(sizeof(char*) * (v->index_f + 1))))
		exit(EXIT_FAILURE);
	if (!(v->directory = (char**)malloc(sizeof(char*) * (v->index_d + 1))))
		exit(EXIT_FAILURE);
	while (v->index_d > 0)
		v->directory[v->index_d--] = NULL;
	while (v->index_f > 0)
		v->files[v->index_f--] = NULL;
}

static void		initialize_path(t_var *v, char **av)
{
	int		tmp;
	int		i;
	int		count;

	count = 0;
	i = 0;
	tmp = 0;
	while (av[++i])
	{
		if (ft_strcmp(av[i], "--") == 0)
		{
			tmp++;
			continue ;
		}
		if (av[i][0] == '-' && v->index_d == 0
				&& v->index_f == 0 && v->index_n == 0 && tmp == 0)
			continue ;
		initialize_path_p2(v, av, i);
		count++;
	}
	if (count >= 1 && v->index_f == 0 && v->index_d == 0)
		exit(EXIT_FAILURE);
	malloc_path(v);
}

static void		initialize(t_var *v, t_flags *f, char **av, int ac)
{
	v->path = "./";
	v->first = NULL;
	v->mid = NULL;
	v->last = NULL;
	v->len_n = 0;
	v->len = 0;
	v->len_u = 0;
	v->len_g = 0;
	v->len_l = 0;
	v->len_s = 0;
	v->len_dmaj = 0;
	v->len_dmin = 0;
	v->index_f = 0;
	v->index_d = 0;
	v->index_n = 0;
	v->mtime = 0;
	v->is_link = 0;
	if (ac > 1)
		initialize_path(v, av);
	f->mod = 0;
	f->l = 0;
	f->t = 0;
	f->r = 0;
	f->a = 0;
	f->rec = 0;
}

void			free_multi_path(t_var *v)
{
	int i;

	i = 0;
	while (i < v->index_f)
		free(v->files[i++]);
	free(v->files);
	i = 0;
	while (i < v->index_d)
		free(v->directory[i++]);
	free(v->directory);
}

int				main(int ac, char **av)
{
	char	*str_rec;
	t_var	v;
	t_flags	f;

	initialize(&v, &f, av, ac);
	if (ac == 1)
		return (print_ls(&v, &f));
	if (ac > 1)
		ft_check_flag(av, &f, &v);
	if (v.index_f == 0 && v.index_d == 0 && v.index_n == 0)
		free_multi_path(&v);
	else
	{
		multi_path(&v, &f);
		return (0);
	}
	if (f.rec == 1)
	{
		str_rec = ft_strdup(v.path);
		ft_recursive_flag(str_rec, &f, &v);
		free(v.mid);
		free(str_rec);
		return (0);
	}
	return (print_ls(&v, &f));
}
