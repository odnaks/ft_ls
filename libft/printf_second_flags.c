/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_second_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 10:45:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	zvezda(t_prt *prt)
{
	int	d;

	d = va_arg(*(prt->ap), int);
	prt->flag->width = 1;
	prt->flag->num = d;
	prt->i++;
}

int			printf_second_flags(t_prt *prt)
{
	if (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57)
	{
		prt->flag->width = 1;
		prt->flag->num = ft_atoi(&(prt->format[prt->i]));
		while (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57
			&& prt->format[prt->i])
			prt->i++;
	}
	if (prt->format[prt->i] == '*')
		zvezda(prt);
	if (prt->format[prt->i] == '.')
	{
		prt->flag->dot = 1;
		prt->i++;
	}
	if (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57)
	{
		prt->flag->toch = ft_atoi(&(prt->format[prt->i]));
		while (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57
			&& prt->format[prt->i])
			prt->i++;
	}
	return (0);
}
