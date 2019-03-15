/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo_foo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 00:25:39 by drestles          #+#    #+#             */
/*   Updated: 2019/03/16 00:53:02 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			l_format_print_dev_help(char *file, t_format *format)
{
	if (obj_type(file) == 2 || obj_type(file) == 3)
		ft_printf("%s %*d %-*s  %*d, %*d %s %s\n", format->chmod,
				format->max0, vtorya_hernya(file), format->max1, format->user,
				format->max3, get_major(file),
				format->max4, get_minor(file), format->date, format->name);
	else
		ft_printf("%s %*d %-*s  %*s %*lld %s %s\n", format->chmod,
				format->max0, vtorya_hernya(file), format->max1, format->user,
				format->max4, "     ", format->max5,
				get_size(file), format->date, format->name);
	free_format(format);
}

void			format_max(char *file, t_format *format, t_ls *ls)
{
	char	*user;
	char	*group;

	format->max = ft_intlen(vtorya_hernya(file));
	if (format->max > format->max0)
		format->max0 = format->max;
	user = get_user(file, ls);
	format->max = ft_strlen(user);
	free(user);
	if (format->max > format->max1)
		format->max1 = format->max;
	group = get_group(file, ls);
	format->max = ft_strlen(group);
	free(group);
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

int				format_rows_objs(char **objs, int n, t_ls *ls)
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
				ft_printf("%-*s", format.max, objs[j]);
			k++;
		}
		ft_printf("\n");
	}
	return (0);
}

void			print_dev(t_format *format, char *file, int type)
{
	if (type == 0)
		printf("%s %*d %-*s  %-*s  %*d, %*d %s %s\n", format->chmod,
			format->max0, vtorya_hernya(file), format->max1, format->user,
			format->max2, format->group, format->max3, get_major(file),
			format->max4, get_minor(file), format->date, format->name);
	else
		printf("%s %*d %-*s  %-*s  %*lld %s %s\n", format->chmod,
			format->max0, vtorya_hernya(file), format->max1, format->user,
			format->max2, format->group, format->max3 + format->max4 + 2,
			get_size(file), format->date, format->name);
}
