/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_l_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:56:26 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:53:07 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_attr(const char *path)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;

	acl = NULL;
	xattr = 0;
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
	{
		acl_free(acl);
		return (1);
	}
	else if (acl != NULL)
	{
		acl_free(acl);
		return (2);
	}
	return (0);
}

static void	chmod_help_2(struct stat st, char **chmod, mode_t perm)
{
	(*chmod)[1] = (perm & S_IRUSR) ? 'r' : '-';
	(*chmod)[2] = (perm & S_IWUSR) ? 'w' : '-';
	(*chmod)[3] = (perm & S_IXUSR) ? 'x' : '-';
	(*chmod)[4] = (perm & S_IRGRP) ? 'r' : '-';
	(*chmod)[5] = (perm & S_IWGRP) ? 'w' : '-';
	(*chmod)[6] = (perm & S_IXGRP) ? 'x' : '-';
	(*chmod)[7] = (perm & S_IROTH) ? 'r' : '-';
	(*chmod)[8] = (perm & S_IWOTH) ? 'w' : '-';
	(*chmod)[9] = (perm & S_IXOTH) ? 'x' : '-';
	if (st.st_mode & 512)
		(*chmod)[9] = ((*chmod)[9] == 'x' ? 't' : 'T');
	if (st.st_mode & 1024)
		(*chmod)[6] = ((*chmod)[6] == 'x' ? 's' : 'S');
	if (st.st_mode & 2048)
		(*chmod)[3] = ((*chmod)[3] == 'x' ? 's' : 'S');
}

static void	chmod_help(struct stat st, char **chmod)
{
	mode_t	perm;

	perm = st.st_mode;
	if ((st.st_mode & S_IFMT) == S_IFREG)
		(*chmod)[0] = '-';
	else if ((st.st_mode & S_IFMT) == S_IFDIR)
		(*chmod)[0] = 'd';
	else if ((st.st_mode & S_IFMT) == S_IFCHR)
		(*chmod)[0] = 'c';
	else if ((st.st_mode & S_IFMT) == S_IFBLK)
		(*chmod)[0] = 'b';
	else if ((st.st_mode & S_IFMT) == S_IFLNK)
		(*chmod)[0] = 'l';
	else if ((st.st_mode & S_IFMT) == S_IFIFO)
		(*chmod)[0] = 'p';
	else if ((st.st_mode & S_IFMT) == S_IFSOCK)
		(*chmod)[0] = 's';
	chmod_help_2(st, chmod, perm);
}

char		*get_chmod(char *path)
{
	struct stat	st;
	char		*chmod;

	chmod = malloc(sizeof(char) * 11 + 1);
	if (lstat(path, &st) == 0)
	{
		chmod_help(st, &chmod);
		if (get_attr(path) == 1)
			chmod[10] = '@';
		else if (get_attr(path) == 2)
			chmod[10] = '+';
		else
			chmod[10] = ' ';
		chmod[11] = '\0';
	}
	else
		chmod[0] = '0';
	return (chmod);
}

int			vtorya_hernya(const char *path)
{
	DIR				*d;
	int				count;
	struct dirent	*dir;
	struct stat		st;

	count = 0;
	lstat(path, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		if ((d = opendir(path)))
		{
			while ((dir = readdir(d)) != NULL)
				count++;
			closedir(d);
		}
	}
	else
		count = 1;
	return (count);
}
