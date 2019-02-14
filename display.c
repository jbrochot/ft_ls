/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:42:44 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/12 14:16:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	ft_display_type(struct stat st)
{
	if (S_ISDIR(st.st_mode))
		ft_printf("d");
	else if (S_ISCHR(st.st_mode))
		ft_printf("c");
	else if (S_ISBLK(st.st_mode))
		ft_printf("b");
	else if (S_ISLNK(st.st_mode))
		ft_printf("l");
	else if (S_ISFIFO(st.st_mode))
		ft_printf("p");
	else if (S_ISSOCK(st.st_mode))
		ft_printf("s");
	else if (S_ISREG(st.st_mode))
		ft_printf("-");
}

void	ft_display_rights(struct stat st)
{
	ft_printf( (st.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf( (st.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf( (st.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf( (st.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf( (st.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf( (st.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf( (st.st_mode & S_IROTH) ? "r" : "-");
	ft_printf( (st.st_mode & S_IWOTH) ? "w" : "-");
	ft_printf( (st.st_mode & S_IXOTH) ? "x" : "-");
}

void	ft_display_usr_grp(struct stat st)
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	ft_printf(" %s", usr->pw_name);
	ft_printf("  %s", grp->gr_name);
}

void	ft_display_long(t_flags *flag, t_var *v)
{
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		if (stat(ft_strjoin(v->path, diread->d_name), &st) < 0)
			return ;
		ft_display_type(st);
		ft_display_rights(st);
		ft_printf("  %3d", st.st_nlink);
		ft_display_usr_grp(st);
		ft_printf("  %5d", st.st_size);
		ft_printf(" %.24s", ft_strsub(ctime(&st.st_mtime), 4, 12));
		ft_printf("  %s", diread->d_name);
		ft_printf("\n");
	}
	closedir(v->dir);
}

void	ft_display(t_flags *flag, t_var *v)
{
	struct stat st;
	if (flag->l == 1)
	{
		ft_display_long(flag, v);
		return ;
	}
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		if (v->path_end != NULL)
		{
			if (ft_strcmp(v->path, ".") != 0)
				ft_printf("%s", v->path);
			ft_printf("%s\n", v->path_end);
			break ;
		}
		else
			ft_printf("%-*s", 17, diread->d_name);
	}
	closedir(v->dir);
}
