/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:38:57 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/22 16:11:33 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ft_ls.h"

struct dirent	*diread;
struct stat		st;
struct tm		*date;

typedef struct s_var
{
	DIR		*save;
	DIR		*dir;
	char	invalid;
	char	*path;
	char	*path_end;
	char	**path_long;
	char	**stock_d;
	int		c_dir;
	size_t	len;
	int		len_file;
	int		len_link;
	time_t	time;
	time_t	time_m;
	time_t	time_l;
	char	*first;
	char	*mid;
	char	*last;
	int		name_count;
	int		file_path;
	char	*p_stat;
	char	*p_slash;
	char	*p_recu;
	int		is_link;
}				t_var;

typedef struct s_flags
{
	int l;
	int R;
	int a;
	int r;
	int t;
	int mod;
}				t_flags;

#endif
