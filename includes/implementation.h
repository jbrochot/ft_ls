/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:43:07 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/15 16:22:16 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPLEMENTATION_H
# define IMPLEMENTATION_H

# include "struct.h"

void	ft_check_flag(int nb, char **av, t_flags *flag, t_var *v);
void	ft_initialize(t_flags *flag, t_var *v);
void	ft_usage(t_var *v, char *str, int mod);
void	ft_display(t_flags *flag, t_var *var);
void	ft_display_long(t_flags *flag, t_var *var);
void	ft_display_std(t_flags *flag, t_var *var);
void	ft_display_type(struct stat st);
void	ft_display_rights(struct stat st);
void	ft_display_usr_grp(struct stat st);
int		ft_ls_no_flag(t_var *v);
void	ft_print_name(struct dirent diread, t_var *v);
void	ft_recursive_flag(char *str, t_flags *flag, t_var *v);
int		ft_nbrlen(int nb);
int		ft_count_blocks(t_var *v);

#endif
