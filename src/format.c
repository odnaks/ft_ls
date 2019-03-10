/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 10:01:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/10 15:33:14 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_format(t_format *format)
{
	format->max0 = 0;
	format->max1 = 0;
	format->max2 = 0;
	format->max3 = 0;
	format->max4 = 0;
	format->max5 = 0;
}

int		format_rows(t_ls *ls)
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
				printf("%-*s", format.max, ls->files[j]);
			k++;
		}
		printf("\n");
	}
	return (0);
}

int		format_rows_objs(char **objs, int n, t_ls *ls)
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
	format.max_row = max_rows(format.count_col, n);
	i = -1;
	while (++i < format.max_row)
	{
		k = 0;
		while (k < format.count_col)
		{
			j = i + k * format.max_row;
			if (j < n)
				printf("%-*s", format.max, objs[j]);
			k++;
		}
		printf("\n");
	}
	return (0);
}

void	format_max(char *file, t_format *format)
{
	format->max = ft_intlen(vtorya_hernya(file));
	if (format->max > format->max0)
		format->max0 = format->max;
	format->max = ft_strlen(get_user(file));
	if (format->max > format->max1)
		format->max1 = format->max;
	format->max = ft_strlen(get_group(file));
	if (format->max > format->max2)
		format->max2 = format->max;
	format->max = ft_intlen(get_major(file));
	if (format->max > format->max3)
		format->max3 = format->max;
	format->max = ft_intlen(get_minor(file));
	if (format->max > format->max4)
		format->max4 = format->max;
	format->max = ft_intlen(get_size(file));
	if (format->max > format->max5)
		format->max5 = format->max;
}

int		l_format_rows(t_ls *ls)
{
	t_format	format;
	int			i;

	init_format(&format);
	i = 0;
	while (i < ls->index_f)
	{
		format_max(ls->files[i], &format);
		i++;
	}
	i = 0;
	while (i < ls->index_f)
	{
		format.chmod = get_chmod(ls->files[i]);
		format.user = get_user(ls->files[i]);
		format.group = get_group(ls->files[i]);
		format.date = get_last_time(ls->files[i]);
		format.name = put_link(ls->files[i]);
		printf("%s %*d %*s %*s %*lld %s %s\n", format.chmod, format.max0,
		vtorya_hernya(ls->files[i]), format.max1, format.user, format.max2,
		format.group, format.max5, get_size(ls->files[i]),
		format.date, format.name);
		free(format.name);
		free(format.chmod);
		free(format.date);
		i++;
	}
	return (0);
}
