/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 10:28:46 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/12 13:54:30 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static char		*ft_get_path(char *str, t_var *v)
{
	int start;
	int end;

	start = 0;
	while (str[start])
		start++;
	end = start;
	while (str[start] != '/')
		start--;
	if ((v->dir = opendir(ft_strsub(str, 0, start))) == NULL)
	{
		ft_usage(v, str, 0);
		exit(EXIT_FAILURE);
	}
	v->path_end = ft_strsub(str, start + 1, end - start);
	v->path = ft_strsub(str, 0, start + 1);
	return (ft_strsub(str, 0, start));
}

static int		ft_check_path(char *str, t_var *v)
{
	if ((v->dir = opendir(str)) == NULL && ft_strchr(str, '/') != NULL)
		v->dir = opendir(ft_get_path(str, v));
	else if ((v->dir = opendir(str)) == NULL && ft_strchr(str, '/') == NULL)
	{
		v->dir = opendir("./");
		v->path_end = str;
	}
	else
	{
		v->path = ft_strjoin(str, "/");
		return (ft_strlen(str));
	}
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (ft_strcmp(diread->d_name, v->path_end) != 0)
			continue ;
		else if (ft_strcmp(diread->d_name, v->path_end) == 0)
		{
			closedir(v->dir);
			return (ft_strlen(str));
		}
	}
	ft_usage(v, str, 0);
	closedir(v->dir);
	exit(EXIT_FAILURE);
}

static int		ft_check_str(char *str, t_var *v, t_flags *flag)
{
	int i;

	i = 0;
	flag->mod = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'l' || str[i] == 'R' || str[i] == 'a' || str[i] == 'r'
				|| str[i] == 't')
			i++;
		flag->mod = 1;
	}
	else
		i = ft_check_path(str, v);
	if (i == ft_strlen(str))
		return (1);
	else
	{
		v->invalid = str[i];
		ft_usage(v, str, 1);
	}
	return (0);
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
			flag->R = 1;
		if (str[i] == 'a')
			flag->a = 1;
		if (str[i] == 'r')
			flag->r = 1;
		if (str[i] == 't')
			flag->t = 1;
		i++;
	}
}

void			ft_check_flag(int nb, char **av, t_flags *flag, t_var *v)
{
	int i;

	i = 1;
	while (i <= nb)
	{
		if (ft_check_str(av[i], v, flag) == 0)
			exit(EXIT_FAILURE);
		else
			ft_set_flag(av[i], flag);
		i++;
	}
}
