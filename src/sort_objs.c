/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:14:32 by drestles          #+#    #+#             */
/*   Updated: 2019/03/15 23:36:14 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_rec_objs(char ***obj, int n)
{
	int		i;
	int		med;
	char	*tmp;

	n--;
	i = 0;
	med = n / 2;
	while (i < med)
	{
		tmp = (*obj)[i];
		(*obj)[i] = (*obj)[n - i];
		(*obj)[n - i] = tmp;
		i++;
	}
}

static void	sort_ascii_objs(char **a, char **b)
{
	char	*tmp;

	if (ft_strcmp(*a, *b) > 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

static void	sort_time_objs(char **a, char **b, t_ls *ls)
{
	char	*tmp;

	if (get_time(*a, *b, ls) >= 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if (get_time(*a, *b, ls) == 0)
	{
		if (ft_strcmp(*a, *b) > 0)
		{
			tmp = *a;
			*a = *b;
			*b = tmp;
		}
	}
}

char		**sort_objs(char **obj, int n, t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ls->t)
				sort_time_objs(&(obj[i]), &(obj[j]), ls);
			else if (!ls->f)
				sort_ascii_objs(&(obj[i]), &(obj[j]));
			j++;
		}
		i++;
	}
	if (ls->r)
		sort_rec_objs(&obj, n);
	return (obj);
}
