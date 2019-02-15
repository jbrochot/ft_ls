/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:38:57 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/15 16:39:20 by ezonda           ###   ########.fr       */
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
	int		len;
	char	*first;
	char	*mid;
	char	*last;
	int		name_count;
	int		file_path;
	char	*p_stat;
	char	*p_slash;
	char	*p_recu;
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
