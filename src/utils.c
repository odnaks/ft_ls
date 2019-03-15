/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:15:07 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/16 00:53:29 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ft_strlen_two(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

int			is_exist(const char *path)
{
	struct stat	path_stat;

	return (stat(path, &path_stat) == 0);
}

int			ft_intlen(int n)
{
	int i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

int			max_rows(int columns, int amount)
{
	if (amount % columns)
		return ((amount / columns) + 1);
	return (amount / columns);
}

int			count_files(const char *path, t_ls *ls)
{
	DIR				*d;
	int				count;
	struct dirent	*dir;

	count = 0;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] != '.' || ls->a || ls->l_a)
				if ((ls->l_a && dir->d_name[1] != '.'
				&& dir->d_name[1]) || !ls->l_a)
					count++;
		}
		closedir(d);
	}
	return (count);
}
