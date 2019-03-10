/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:56:31 by drestles          #+#    #+#             */
/*   Updated: 2019/03/10 15:17:21 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_user(const char *path)
{
	struct stat		info;
	struct passwd	*pw;

	stat(path, &info);
	pw = getpwuid(info.st_uid);
	return ((char *)pw->pw_name);
}

char	*get_group(const char *path)
{
	struct stat		info;
	struct group	*gr;

	stat(path, &info);
	gr = getgrgid(info.st_gid);
	return ((char *)gr->gr_name);
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

	lstat(path, &st);
	if ((st.st_mode & S_IFMT) == S_IFLNK)
	{
		res = ft_strdup(basename(path));
		res = ft_strjoin_left(res, " -> ");
		res = ft_strjoin_left(res, basename(realpath(path, NULL)));
		return (res);
	}
	return (basename(path));
}
