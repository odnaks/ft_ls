/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_def_percentage.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 10:34:39 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_def_percentage(t_prt *prt)
{
	while (prt->format[prt->i] == ' ')
		prt->i++;
	if (prt->format[prt->i] == '%')
	{
		if (prt->flag->width && prt->flag->num-- > 0 && !prt->flag->minus)
		{
			while (prt->flag->num-- > 0)
				prt->buff[prt->j++] = ' ';
			prt->buff[prt->j++] = prt->format[prt->i++];
		}
		else
			prt->buff[prt->j++] = prt->format[prt->i++];
		while (prt->flag->num-- > 0)
			prt->buff[prt->j++] = ' ';
	}
	return (0);
}
