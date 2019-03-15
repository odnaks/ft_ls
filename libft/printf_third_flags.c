/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_third_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 10:45:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	third_flags_two(t_prt *prt)
{
	if (prt->format[prt->i] == 'L')
		prt->flag->ll = 1;
	prt->i++;
	return (0);
}

static int	third_flags_one(t_prt *prt)
{
	if (prt->format[prt->i] == 'h')
	{
		if (prt->format[prt->i + 1] == 'h')
		{
			prt->flag->hh = 1;
			prt->i++;
		}
		else
			prt->flag->h = 1;
	}
	if (prt->format[prt->i] == 'l')
	{
		if (prt->format[prt->i + 1] == 'l')
		{
			prt->flag->ll = 1;
			prt->i++;
		}
		else
			prt->flag->l = 1;
	}
	prt->i++;
	return (0);
}

int			printf_third_flags(t_prt *prt)
{
	if (prt->format[prt->i] == 'h' || prt->format[prt->i] == 'l')
		third_flags_one(prt);
	if (prt->format[prt->i] == 'L')
		third_flags_two(prt);
	return (0);
}
