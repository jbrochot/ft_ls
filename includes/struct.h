/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:38:57 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/12 13:49:04 by ezonda           ###   ########.fr       */
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
	DIR		*dir;
	DIR		*save;
	char	invalid;
	char	*path;
	char	*path_end;
	int		len;
	char	*first;
	char	*mid;
	char	*last;
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
