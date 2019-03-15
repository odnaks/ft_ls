/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:53:19 by pcollio-          #+#    #+#             */
/*   Updated: 2019/03/16 00:53:04 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			init_format(t_format *format)
{
	format->max0 = 0;
	format->max1 = 0;
	format->max2 = 0;
	format->max3 = 0;
	format->max4 = 0;
	format->max5 = 0;
}

void			free_format_mini(t_format *format)
{
	free(format->chmod);
	free(format->user);
}

void			free_format(t_format *format)
{
	free(format->date);
	free(format->chmod);
	free(format->name);
	free(format->user);
	free(format->group);
}

void			put_usage(char a)
{
	ft_printf("ls: illegal option -- %c\n", a);
	ft_printf("usage: ls [-ARaflnort1] [file ...]");
	exit(1);
}
