/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:57:06 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 15:17:08 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static int		close_dir(t_var *v, int i, char *s1, char *s2)
{
	if (i == 0 || i == 2)
	{
		free(s1);
		free(s2);
	}
	if (i == 1 || i == 0)
		closedir(v->dir);
	if (i == 0)
		return (2);
	return (1);
}

int				ft_check_path_p2(char *str, t_var *v)
{
	closedir(v->dir);
	if (str[ft_strlen(str) - 1] != '/')
		v->directory[v->index_d] = ft_strjoin(str, "/");
	else
		v->directory[v->index_d] = ft_strdup(str);
	v->index_d++;
	return (ft_strlen(str));
}

int				is_file(char *s, t_var *v)
{
	v->dir = opendir("./");
	while ((diread = readdir(v->dir)) != NULL)
		if (ft_strcmp(diread->d_name, s) == 0)
			return (close_dir(v, 1, NULL, NULL));
	closedir(v->dir);
	if (lstat(s, &st) < 0)
		return (0);
	if (S_ISLNK(st.st_mode))
		return (1);
	return (0);
}

int				is_file_n(char *s, t_var *v)
{
	char	*path_d;
	char	*path;

	if (ft_strchr(s, '/') != NULL)
	{
		v->len = ft_strlen(s);
		v->len_n = v->len;
		while (s[v->len] != '/')
			v->len--;
		path_d = ft_strsub(s, 0, v->len);
		path = ft_strsub(s, v->len + 1, v->len_n - v->len);
		if ((v->dir = opendir(path_d)) == NULL)
		{
			ft_usage(v, s, 0);
			return (close_dir(v, 2, path_d, path));
		}
		while ((diread = readdir(v->dir)) != NULL)
			if (ft_strcmp(diread->d_name, path) == 0)
				return (close_dir(v, 0, path_d, path));
		close_dir(v, 2, path_d, path);
	}
	ft_usage(v, s, 0);
	return (0);
}

int				is_directory(char *s)
{
	if (lstat(s, &st) < 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}
