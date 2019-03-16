/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 10:01:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:23:29 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		l_format_rows_help(t_ls *ls, t_format *format, int i)
{
	if (ls->o)
		ft_printf("%s %*d %*s %*ld %s %s\n", format->chmod, format->max0,
				vtorya_hernya(ls->files[i]), format->max1, format->user,
				format->max5, get_size(ls->files[i]),
				format->date, format->name);
	else
		ft_printf("%s %*d %*s %*s %*d %s %s\n", format->chmod, format->max0,
				vtorya_hernya(ls->files[i]), format->max1, format->user,
				format->max2, format->group, format->max5,
				get_size(ls->files[i]), format->date, format->name);
	free_format(format);
}

void			one_format_rows(t_ls *ls)
{
	int			i;

	i = 0;
	while (i < ls->index_f)
	{
		ft_printf("%s\n", basename(ls->files[i]));
		i++;
	}
}

int				format_rows(t_ls *ls)
{
	struct winsize	w;
	t_format		format;
	int				i;
	int				j;
	int				k;

	ioctl(0, TIOCGWINSZ, &w);
	format.width = w.ws_col;
	format.max = ls->max + (8 - (ls->max % 8));
	format.count_col = format.width / format.max;
	format.max_row = max_rows(format.count_col, ls->index_f);
	i = -1;
	while (++i < format.max_row)
	{
		k = 0;
		while (k < format.count_col)
		{
			j = i + k * format.max_row;
			if (j < ls->index_f)
				ft_printf("%-*s", format.max, ls->files[j]);
			k++;
		}
		ft_printf("\n");
	}
	return (0);
}

void			one_format_rows_objs(char **objs, int n)
{
	int			i;

	i = 0;
	while (i < n)
	{
		ft_printf("%s\n", basename(objs[i]));
		i++;
	}
}

int				l_format_rows(t_ls *ls)
{
	t_format	format;
	int			i;

	init_format(&format);
	i = 0;
	while (i < ls->index_f)
	{
		format_max(ls->files[i], &format, ls);
		i++;
	}
	i = 0;
	while (i < ls->index_f)
	{
		format.chmod = get_chmod(ls->files[i]);
		format.user = get_user(ls->files[i], ls);
		format.group = get_group(ls->files[i], ls);
		format.date = get_last_time(ls->files[i]);
		format.name = put_link(ls->files[i]);
		l_format_rows_help(ls, &format, i);
		i++;
	}
	return (0);
}
