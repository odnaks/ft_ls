/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_first_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 10:45:49 by drestles          #+#    #+#             */
/*   Updated: 2019/02/26 18:08:24 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	init_flags(t_prt *prt)
{
	prt->flag = malloc(sizeof(t_flag));
	prt->flag->sharp = 0;
	prt->flag->nul = 0;
	prt->flag->minus = 0;
	prt->flag->plus = 0;
	prt->flag->space = 0;
	prt->flag->h = 0;
	prt->flag->hh = 0;
	prt->flag->l = 0;
	prt->flag->ll = 0;
	prt->flag->width = 0;
	prt->flag->dot = 0;
	prt->flag->toch = 0;
	prt->flag->num = 0;
	prt->flag->point = 0;
	prt->flag->nn = 0;
	return (0);
}

int			printf_first_flags(t_prt *prt)
{
	init_flags(prt);
	while (prt->format[prt->i] == '#' || prt->format[prt->i] == '0'
	|| prt->format[prt->i] == '-' || prt->format[prt->i] == '+'
	|| prt->format[prt->i] == ' ')
	{
		if (prt->format[prt->i] == '#')
			prt->flag->sharp = 1;
		if (prt->format[prt->i] == '0')
			prt->flag->nul = 1;
		if (prt->format[prt->i] == '-')
			prt->flag->minus = 1;
		if (prt->format[prt->i] == '+')
			prt->flag->plus = 1;
		if (prt->format[prt->i] == ' ')
			prt->flag->space = 1;
		prt->i++;
	}
	return (0);
}
