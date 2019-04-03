/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:00:20 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:15:36 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	rm_av_t(char **av, int index)
{
	while (av[index])
	{
		av[index] = av[index + 1];
		index++;
	}
	av[index] = NULL;
}

void	ft_usage(t_var *v, char *str, int mod)
{
	if (mod == 1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(v->invalid, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ./ft_ls [-lRart] [file ...]", 2);
	}
	else if (mod == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(ft_dirchr(str, '/'), 2);
		perror(" ");
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(str, 2);
		perror(" ");
	}
}

int		invalid_case(char *str, size_t i, t_var *v)
{
	if (i == ft_strlen(str))
		return (1);
	else
	{
		v->invalid = str[i];
		ft_usage(v, str, 1);
	}
	return (0);
}

int		free_long(char *name, char *pathname, int mod)
{
	free(pathname);
	free(name);
	if (mod == 0)
		return (-1);
	else
		return (0);
}

int		ft_count_blocks(t_var *v, t_flags *flag)
{
	char	*name;
	int		count;
	char	*pathname;

	count = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		name = ft_strdup(diread->d_name);
		pathname = ft_strjoin(v->path, name);
		free(name);
		if (lstat(pathname, &st) < 0)
		{
			free(pathname);
			closedir(v->dir);
			return (-1);
		}
		count += st.st_blocks;
		free(pathname);
	}
	closedir(v->dir);
	return (count);
}
