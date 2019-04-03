/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:03:52 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 16:39:24 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		ft_display_type(t_var *v)
{
	if (S_ISDIR(st.st_mode))
		ft_printf("d");
	else if (S_ISCHR(st.st_mode))
	{
		v->is_dev = 1;
		ft_printf("c");
	}
	else if (S_ISBLK(st.st_mode))
		ft_printf("b");
	else if (S_ISLNK(st.st_mode))
	{
		ft_printf("l");
		v->is_link = 1;
	}
	else if (S_ISFIFO(st.st_mode))
		ft_printf("p");
	else if (S_ISSOCK(st.st_mode))
		ft_printf("s");
	else if (S_ISREG(st.st_mode))
		ft_printf("-");
}

static void		ft_display_rights(void)
{
	ft_printf((st.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((st.st_mode & S_IWUSR) ? "w" : "-");
	if (st.st_mode & S_IXUSR)
		ft_printf((st.st_mode & S_ISUID) ? "s" : "x");
	else if (st.st_mode & S_ISUID)
		ft_printf("S");
	else
		ft_printf("-");
	ft_printf((st.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((st.st_mode & S_IWGRP) ? "w" : "-");
	if (st.st_mode & S_IXGRP)
		ft_printf((st.st_mode & S_ISGID) ? "s" : "x");
	else if (st.st_mode & S_ISGID)
		ft_printf("S");
	else
		ft_printf("-");
	ft_printf((st.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((st.st_mode & S_IWOTH) ? "w" : "-");
	if (st.st_mode & S_IXOTH)
		ft_printf((st.st_mode & S_ISVTX) ? "t" : "x");
	else if (st.st_mode & S_ISVTX)
		ft_printf("T");
	else
		ft_printf("-");
}

static void		ft_display_usr_grp(t_var *v)
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(st.st_uid);
	if (usr != NULL)
		ft_printf(" %-*s", v->len_u, usr->pw_name);
	else
		ft_printf(" %-*ld", v->len_u, (long)st.st_uid);
	grp = getgrgid(st.st_gid);
	if (grp != NULL)
		ft_printf("  %-*s", v->len_g, grp->gr_name);
	else
		ft_printf("  %-*ld", v->len_g, (long)st.st_gid);
}

static void		ft_display_attr(t_var *v)
{
	char	*pathname;

	pathname = ft_strjoin(v->path, v->first);
	if (listxattr(pathname, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_printf("@");
	else
		ft_printf(" ");
	free(pathname);
}

int				print_long(t_var *v)
{
	char	*name;
	char	*pathname;
	char	*time;

	name = ft_strdup(v->first);
	pathname = v->l_multi != 1 ? ft_strjoin(v->path, name) : ft_strdup(name);
	if (lstat(pathname, &st) < 0)
		return (free_long(name, pathname, 0));
	ft_display_type(v);
	ft_display_rights();
	ft_display_attr(v);
	ft_printf(" %*d", v->len_l, st.st_nlink);
	ft_display_usr_grp(v);
	if (v->is_dev == 1)
		ft_display_dev(v);
	else
		ft_printf("  %*d", v->len_s, st.st_size);
	time = ft_strsub(ctime(&st.st_mtime), 20, 4);
	ft_display_time(time);
	ft_printf("%s", v->first);
	if (v->is_link == 1)
		ft_get_link(v, pathname);
	ft_printf("\n");
	return (free_long(name, pathname, 1));
}
