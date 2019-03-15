/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:25:18 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:53:14 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	l_format_norm(char *file, t_format *format, t_ls *ls)
{
	format->chmod = get_chmod(file);
	format->user = get_user(file, ls);
	format->group = get_group(file, ls);
	format->date = get_last_time(file);
	format->name = put_link(file);
	if (ls->o)
		ft_printf("%s %*d %-*s  %*d %s %s\n", format->chmod, format->max0,
				vtorya_hernya(file), format->max1, format->user,
				format->max5, get_size(file), format->date, format->name);
	else
		ft_printf("%s %*d %-*s  %-*s  %*d %s %s\n", format->chmod, format->max0,
				vtorya_hernya(file), format->max1, format->user, format->max2,
				format->group, format->max5, get_size(file), format->date,
				format->name);
	free_format(format);
}

static void	l_format_print_dev(char *file, t_format *format, t_ls *ls)
{
	format->chmod = get_chmod(file);
	if (format->chmod[0] == '0')
	{
		free(format->chmod);
		return ;
	}
	format->user = get_user(file, ls);
	if (format->user[0] == '0')
	{
		free_format_mini(format);
		return ;
	}
	format->group = get_group(file, ls);
	format->date = get_last_time(file);
	format->name = put_link(file);
	if (ls->o)
		l_format_print_dev_help(file, format);
	else if (obj_type(file) == 2 || obj_type(file) == 3)
		print_dev(format, file, 0);
	else
		print_dev(format, file, 1);
	if (!ls->o)
		free_format(format);
}

static void	l_format_dev(t_ls *ls, char **objs, t_format *format, int n)
{
	int		i;
	char	*file;

	i = 0;
	while (i < n)
	{
		file = ft_strjoin(ls->path, objs[i]);
		l_format_print_dev(file, format, ls);
		free(file);
		i++;
	}
}

static void	l_format_rows_objs_format_and_free(t_ls *ls,
	t_format *format, char ***objs, int i)
{
	char	*file;

	file = ft_strjoin(ls->path, (*objs)[i]);
	format_max(file, format, ls);
	free(file);
}

int			l_format_rows_objs(char **objs, int n, t_ls *ls)
{
	t_format	format;
	int			i;
	char		*file;

	init_format(&format);
	format.total = get_total_size(objs, ls);
	ft_printf("total %d\n", format.total);
	i = -1;
	while (++i < n)
		l_format_rows_objs_format_and_free(ls, &format, &objs, i);
	if (ft_strstr(ls->path, "/dev"))
		l_format_dev(ls, objs, &format, n);
	else
	{
		i = -1;
		while (++i < n)
		{
			file = ft_strjoin(ls->path, objs[i]);
			l_format_norm(file, &format, ls);
			free(file);
		}
	}
	return (0);
}
