/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:54:43 by drestles          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	pow_10(int n)
{
	long double	p;

	p = 1;
	while (n > 0)
	{
		p *= 10;
		n--;
	}
	return (p);
}

long int	abs_l(long int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int			printf_handle_p(t_prt *prt)
{
	prt->flag->sharp = 1;
	prt->flag->l = 1;
	prt->flag->point = 1;
	printf_handle_x(prt);
	return (0);
}
