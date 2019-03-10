/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:25:18 by drestles          #+#    #+#             */
/*   Updated: 2019/03/10 15:33:33 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	l_format_norm(char *file, t_format *format)
{
	format->chmod = get_chmod(file);
	format->user = get_user(file);
	format->group = get_group(file);
	format->date = get_last_time(file);
	format->name = put_link(file);
	printf("%s %*d %-*s  %-*s  %*lld %s %s\n", format->chmod, format->max0,
	vtorya_hernya(file), format->max1, format->user, format->max2,
	format->group, format->max5, get_size(file), format->date, format->name);
	free(format->name);
	free(format->chmod);
}

static void	l_format_print_dev(char *file, t_format *format)
{
	format->chmod = get_chmod(file);
	format->user = get_user(file);
	format->group = get_group(file);
	format->date = get_last_time(file);
	format->name = put_link(file);
	printf("%s %*d %-*s  %-*s  %*d, %*d %s %s\n", format->chmod,
	format->max0, vtorya_hernya(file), format->max1, format->user,
	format->max2, format->group, format->max3, get_major(file),
	format->max4, get_minor(file), format->date, format->name);
	free(format->name);
	free(format->chmod);
	free(format->date);
}

static void	l_format_dev(t_ls *ls, char **objs, t_format *format, int n)
{
	int		i;
	char	*file;

	i = 0;
	while (i < n)
	{
		file = ft_strjoin(ls->path, objs[i]);
		l_format_print_dev(file, format);
		free(file);
		i++;
	}
}

int			l_format_rows_objs(char **objs, int n, t_ls *ls)
{
	t_format	format;
	char		*file;
	int			i;

	init_format(&format);
	format.total = get_total_size(objs, ls);
	printf("total %d\n", format.total);
	i = -1;
	while (++i < n)
	{
		file = ft_strjoin(ls->path, objs[i]);
		format_max(file, &format);
		free(file);
	}
	i = 0;
	if (ft_strstr(ls->path, "/dev"))
		l_format_dev(ls, objs, &format, n);
	i = -1;
	while (++i < n)
	{
		file = ft_strjoin(ls->path, objs[i]);
		l_format_norm(file, &format);
		free(file);
	}
	return (0);
}
