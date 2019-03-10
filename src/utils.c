/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:15:07 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/10 14:35:13 by drestles         ###   ########.fr       */
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
	return (ft_strlen(ft_itoa(n)));
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
			if (dir->d_name[0] != '.' || ls->a)
				count++;
		}
		closedir(d);
	}
	return (count);
}
