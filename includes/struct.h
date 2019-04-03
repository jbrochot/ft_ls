/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:38:57 by jebrocho          #+#    #+#             */
/*   Updated: 2019/04/03 15:13:33 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_ls.h"

struct dirent	*diread;
struct stat		st;
struct tm		*date;

typedef struct	s_var
{
	DIR		*dir;
	char	*path;
	char	invalid;
	int		file_path;
	int		c_dir;
	char	**directory;
	int		index_d;
	char	**files;
	int		index_f;
	char	**file_in_dir;
	int		index_n;
	char	*first;
	time_t	ftime;
	char	*last;
	time_t	ltime;
	char	*mid;
	time_t	mtime;
	size_t	len_n;
	int		len;
	int		is_link;
	int		len_s;
	int		len_l;
	int		len_u;
	int		len_g;
	int		is_dev;
	int		len_dmaj;
	int		len_dmin;
	int		l_multi;
	int		counter;
	int		index_path;
}				t_var;

typedef struct	s_flags
{
	int opt_end;
	int mod;
	int l;
	int rec;
	int a;
	int r;
	int t;
}				t_flags;

#endif
