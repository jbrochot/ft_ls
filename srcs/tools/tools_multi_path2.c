/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_multi_path2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:32:01 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/03 15:46:28 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	rev_order(char **tab)
{
	char	*tab_save;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	k = j;
	if (j > 1)
	{
		j--;
		while (i < j)
		{
			tab_save = tab[i];
			tab[i] = tab[j];
			tab[j] = tab_save;
			i++;
			j--;
		}
		tab[k] = NULL;
	}
}

void	multi_display(t_var *v, t_flags *f, int i)
{
	if (v->index_f != 0 || i != 0)
		ft_printf("\n");
	if (i > 0 && f->l == 0)
		ft_printf("\n");
	if (v->index_f != 0 || i != 0 || v->index_d != 1)
		ft_printf("%s:\n", v->directory[i]);
	print_ls(v, f);
}

void	initialize_path_p2(t_var *v, char **av, int i)
{
	if (is_directory(av[i]) == 1)
		v->index_d++;
	else if (is_file(av[i], v) == 1)
		v->index_f++;
	else if (is_file_n(av[i], v) == 2)
		v->index_f++;
	else
		rm_av_t(av, i--);
}

void	algo_multi_time(char **tab, t_var *v, int i, int j)
{
	char *tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
	v->ftime = st.st_mtime;
}
