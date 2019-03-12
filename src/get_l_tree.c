/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:56:28 by drestles          #+#    #+#             */
/*   Updated: 2019/03/10 15:56:46 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_major(char *path)
{
	struct stat	sp;
	int			m;

	stat(path, &sp);
	m = MAJOR(sp.st_rdev);
	return (m);
}

int	get_minor(char *path)
{
	struct stat	sp;
	int			m;

	stat(path, &sp);
	m = MINOR(sp.st_rdev);
	return (m);
}

int	get_time(char *f1, char *f2, t_ls *ls)
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
