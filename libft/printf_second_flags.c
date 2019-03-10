/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_second_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 10:45:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_second_flags(t_prt *prt)
{
	if (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57)
	{
		prt->flag->width = 1;
		prt->flag->num = ft_atoi(&(prt->format[prt->i]));
		while (prt->format[prt->i] >= 48 && prt->format[prt->i] <= 57
			&& prt->format[prt->i])
			prt->i++;
	}
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
