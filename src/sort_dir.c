/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:00:35 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:43:37 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_ascii_dir(t_ls *ls, int i, int j)
{
	char *tmp;

	if (ft_strcmp((ls->dir[i]), (ls->dir[j])) > 0)
	{
		tmp = ls->dir[i];
		ls->dir[i] = ls->dir[j];
		ls->dir[j] = tmp;
	}
}

static void	sort_rec_dir(t_ls *ls)
{
	int		med;
	int		i;
	char	*tmp;

	i = 0;
	med = ls->index_d / 2;
	while (i < med)
	{
		tmp = ls->dir[i];
		ls->dir[i] = ls->dir[ls->index_d - 1 - i];
		ls->dir[ls->index_d - 1 - i] = tmp;
		i++;
	}
}

static void	sort_time_dir(t_ls *ls, int i, int j)
{
	char *tmp;

	if (get_time((ls->dir[i]), (ls->dir[j]), ls) >= 0)
	{
		tmp = ls->dir[i];
		ls->dir[i] = ls->dir[j];
		ls->dir[j] = tmp;
	}
	if (get_time((ls->dir[i]), (ls->dir[j]), ls) == 0)
	{
		if (ft_strcmp((ls->dir[i]), (ls->dir[j])) > 0)
		{
			tmp = ls->dir[i];
			ls->dir[i] = ls->dir[j];
			ls->dir[j] = tmp;
		}
	}
}

void		sort_dir(t_ls *ls)
{
	int	i;
	int	j;

	i = 0;
	while (i < ls->index_d - 1)
	{
		j = i + 1;
		while (j < ls->index_d)
		{
			if (ls->t)
				sort_time_dir(ls, i, j);
			else if (!ls->f)
				sort_ascii_dir(ls, i, j);
			j++;
		}
		i++;
	}
	if (ls->r)
		sort_rec_dir(ls);
}
