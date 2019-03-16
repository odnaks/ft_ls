/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcollio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:56:28 by drestles          #+#    #+#             */
/*   Updated: 2019/03/15 17:33:26 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_major(char *path)
{
	struct stat	sp;
	int			m;

	stat(path, &sp);
	m = MAJOR(sp.st_rdev);
	return (m);
}

int		get_minor(char *path)
{
	struct stat	sp;
	int			m;

	stat(path, &sp);
	m = MINOR(sp.st_rdev);
	return (m);
}

int		get_time(char *f1, char *f2, t_ls *ls)
{
	struct stat	s1;
	struct stat	s2;
	char		*file1;
	char		*file2;

	file1 = ft_strjoin(ls->path, f1);
	file2 = ft_strjoin(ls->path, f2);
	lstat(file1, &s1);
	lstat(file2, &s2);
	free(file1);
	free(file2);
	if (s1.st_mtime < s2.st_mtime)
		return (1);
	if (s1.st_mtime == s2.st_mtime)
		return (0);
	return (-1);
}

off_t	get_total_size(char **files, t_ls *ls)
{
	off_t		total;
	struct stat	st;
	int			i;
	char		*file;

	i = 0;
	total = 0;
	while (files[i] != NULL)
	{
		file = ft_strjoin(ls->path, files[i]);
		lstat(file, &st);
		total += st.st_blocks;
		free(file);
		i++;
	}
	return (total);
}
