/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:20:38 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/10 16:00:16 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			flags(char *args, t_ls *ls)
{
	int i;

	i = 0;
	if (args[i] == '-' && args[i + 1] > 32 && args[i + 1] < 127)
	{
		i++;
		while (args[i] > 32 && args[i] < 127)
		{
			if (args[i] == 'l')
				ls->l = 1;
			else if (args[i] == 'r')
				ls->r = 1;
			else if (args[i] == 'R')
				ls->l_r = 1;
			else if (args[i] == 'a')
				ls->a = 1;
			else if (args[i] == 't')
				ls->t = 1;
			else
				put_usage(args[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

char		**dir_to_str(t_ls *ls)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	str = malloc(sizeof(char*) * (ls->index_d + 1));
	str[ls->index_d] = 0;
	while (i < ls->index_d)
	{
		str[i] = malloc(sizeof(char) * ft_strlen(ls->dir[i] + 1));
		j = 0;
		while (j < (int)ft_strlen(ls->dir[i]))
		{
			str[i][j] = ls->dir[i][j];
			j++;
		}
		str[i][j] = '\0';
		i++;
	}
	free_dirs(ls);
	return (str);
}

void		ls_files(t_ls *ls)
{
	sort(ls);
	if (ls->l)
		l_format_rows(ls);
	else
		format_rows(ls);
}

void		ls_dir(t_ls *ls)
{
	int k;
	int n;

	k = 0;
	n = 0;
	while (k < ls->index_d)
	{
		n = count_files(ls->dir[k], ls);
		free_files(ls);
		malloc_files(n, ls);
		ft_printf("\n%s:\n", ls->dir[k]);
		push_dir_files(ls->dir[k], ls);
		k++;
	}
}

int			obj_type(const char *path)
{
	struct stat	path_stat;

	lstat(path, &path_stat);
	if ((path_stat.st_mode & S_IFMT) == S_IFREG)
		return (0);
	else if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	else if ((path_stat.st_mode & S_IFMT) == S_IFCHR)
		return (2);
	else if ((path_stat.st_mode & S_IFMT) == S_IFBLK)
		return (3);
	else if ((path_stat.st_mode & S_IFMT) == S_IFIFO)
		return (4);
	else if ((path_stat.st_mode & S_IFMT) == S_IFLNK)
		return (5);
	else if ((path_stat.st_mode & S_IFMT) == S_IFSOCK)
		return (7);
	else
		return (-1);
}
