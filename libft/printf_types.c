/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 10:34:39 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	def_types(t_prt *prt)
{
	if (prt->format[prt->i] == TYPE[0])
		printf_handle_s(prt);
	if (prt->format[prt->i] == TYPE[1])
		printf_handle_ls(prt);
	if (prt->format[prt->i] == TYPE[2])
		printf_handle_p(prt);
	if (prt->format[prt->i] == TYPE[3] ||
	prt->format[prt->i] == TYPE[5])
		printf_handle_d(prt);
	if (prt->format[prt->i] == TYPE[6])
		printf_handle_o(prt);
	if (prt->format[prt->i] == TYPE[8])
		printf_handle_u(prt);
	if (prt->format[prt->i] == TYPE[10])
		printf_handle_x(prt);
	if (prt->format[prt->i] == TYPE[11])
		printf_handle_lx(prt);
	if (prt->format[prt->i] == TYPE[12])
		printf_handle_c(prt);
	if (prt->format[prt->i] == TYPE[13])
		printf_handle_lc(prt);
	if (prt->format[prt->i] == TYPE[14])
		printf_handle_f(prt);
	return (0);
}

int			printf_types(t_prt *prt)
{
	if (prt->format[prt->i] == TYPE[0] || prt->format[prt->i] == TYPE[1] ||
	prt->format[prt->i] == TYPE[2] || prt->format[prt->i] == TYPE[3] ||
	prt->format[prt->i] == TYPE[4] || prt->format[prt->i] == TYPE[5] ||
	prt->format[prt->i] == TYPE[6] || prt->format[prt->i] == TYPE[8] ||
	prt->format[prt->i] == TYPE[10] || prt->format[prt->i] == TYPE[11] ||
	prt->format[prt->i] == TYPE[12] || prt->format[prt->i] == TYPE[13] ||
	prt->format[prt->i] == TYPE[14])
	{
		def_types(prt);
		prt->i++;
	}
	return (0);
}
