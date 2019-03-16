/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcollio- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:56:31 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 20:24:02 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_user(const char *path, t_ls *ls)
{
	struct stat		info;
	struct passwd	*pw;

	stat(path, &info);
	if ((pw = getpwuid(info.st_uid)))
	{
		if (ls->n)
			return (ft_itoa(pw->pw_uid));
		return (ft_strdup((char *)pw->pw_name));
	}
	return (ft_strdup("0"));
}

char	*get_group(const char *path, t_ls *ls)
{
	struct stat		info;
	struct group	*gr;

	stat(path, &info);
	gr = getgrgid(info.st_gid);
	if (ls->n)
		return (ft_itoa(gr->gr_gid));
	return (ft_strdup((char *)gr->gr_name));
}

off_t	get_size(char *path)
{
	struct stat	st;
	off_t		size;

	lstat(path, &st);
	size = st.st_size;
	return (size);
}

char	*get_last_time(char *path)
{
	struct stat	st;
	char		*raw_data;
	char		*data;
	int			i;
	int			j;

	j = 0;
	i = 4;
	stat(path, &st);
	raw_data = ctime(&st.st_mtime);
	data = (char *)malloc(sizeof(char) * 16);
	while (i != 16)
		data[j++] = raw_data[i++];
	data[j] = '\0';
	return (data);
}

char	*put_link(char *path)
{
	struct stat	st;
	char		*res;
	char		buf[PATH_MAX + 1];

	lstat(path, &st);
	realpath(path, buf);
	if ((st.st_mode & S_IFMT) == S_IFLNK)
	{
		res = ft_strdup(basename(path));
		res = ft_strjoin_left(res, " -> ");
		res = ft_strjoin_left(res, basename(buf));
		return (res);
	}
	return (ft_strdup(basename(path)));
}
