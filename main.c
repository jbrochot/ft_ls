/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:09:17 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/14 20:16:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		main(int ac, char **av)
{
	t_flags		flag;
	t_var		v;

	ft_initialize(&flag, &v, av);
	if (ac == 1)
		return (ft_ls_no_flag(&v, &flag));
	if (ac > 1)
		ft_check_flag(ac - 1, av, &flag, &v);
	ft_display(&flag, &v);
	return (0);
}
