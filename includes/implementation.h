/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:43:07 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/12 13:33:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPLEMENTATION_H
# define IMPLEMENTATION_H

# include "struct.h"

void	ft_check_flag(int nb, char **av, t_flags *flag, t_var *v);
void	ft_initialize(t_flags *flag, t_var *v);
void	ft_usage(t_var *v, char *str, int mod);
void	ft_display(t_flags *flag, t_var *var);
int		ft_ls_no_flag(t_var *v);
int		ft_nbrlen(int nb);

#endif
