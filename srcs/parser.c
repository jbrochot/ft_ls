/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 10:28:46 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/03 11:04:39 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		ft_get_path(char *str, t_var *v)
{
	v->files[v->index_f] = ft_strdup(str);
	v->index_f++;
	return (ft_strlen(str));
}

static int		ft_check_path(char *str, t_var *v)
{
	v->index_path = 0;
	if (lstat(str, &st) < 0)
		return (0);
	if ((v->dir = opendir(str)) == NULL || S_ISLNK(st.st_mode))
	{
		if (S_ISDIR(st.st_mode))
		{
			v->directory[v->index_d] = ft_strdup(str);
			v->index_d++;
			return (ft_strlen(str));
		}
		else if (ft_strchr(str, '/') != NULL)
			return (ft_get_path(str, v));
		v->index_path++;
	}
	if (v->index_path == 0)
		closedir(v->dir);
	if ((v->dir = opendir(str)) == NULL && ft_strchr(str, '/') == NULL)
	{
		v->files[v->index_f] = ft_strdup(str);
		v->index_f++;
	}
	else
		return (ft_check_path_p2(str, v));
	return (ft_strlen(str));
}

static int		ft_check_str(char *str, t_var *v, t_flags *flag)
{
	size_t i;

	i = 0;
	if (str[i] == '-' && flag->opt_end != 1)
	{
		i++;
		if (str[i] == '-')
		{
			flag->opt_end = 1;
			i++;
		}
		while ((str[i] == 'l' || str[i] == 'R' || str[i] == 'a' || str[i] == 'r'
				|| str[i] == 't') && flag->opt_end != 1)
			i++;
		flag->mod = 1;
	}
	else
	{
		flag->opt_end = 1;
		flag->mod = 0;
		i = ft_check_path(str, v);
	}
	return (invalid_case(str, i, v));
}

static void		ft_set_flag(char *str, t_flags *flag)
{
	int i;

	i = 0;
	while (str[i] != '\0' && flag->mod == 1)
	{
		if (str[i] == 'l')
			flag->l = 1;
		if (str[i] == 'R')
			flag->rec = 1;
		if (str[i] == 'a')
			flag->a = 1;
		if (str[i] == 'r')
			flag->r = 1;
		if (str[i] == 't')
			flag->t = 1;
		i++;
	}
}

void			ft_check_flag(char **av, t_flags *flag, t_var *v)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_check_str(av[i], v, flag) == 0)
			exit(EXIT_FAILURE);
		else
			ft_set_flag(av[i], flag);
		i++;
	}
}
