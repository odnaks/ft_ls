/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:24:58 by rcotter-          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_zero(t_prt *prt)
{
	ft_putstr(prt->buff);
	prt->count_zero += ft_strlen(prt->buff);
	ft_bzero(prt->buff, BUFF_SIZE);
	write(1, "\0", 1);
	prt->count_zero++;
	prt->j = 0;
	return (0);
}

static int	handle_c_flags(t_prt *prt, char *c)
{
	if (prt->flag->minus)
	{
		if (*c)
			prt->buff[prt->j] = *c;
		else
			handle_zero(prt);
		while (--prt->flag->num)
			prt->buff[++prt->j] = ' ';
	}
	else
	{
		while (--prt->flag->num)
			prt->buff[prt->j++] = ' ';
		if (*c)
			prt->buff[prt->j] = *c;
		else
			handle_zero(prt);
	}
	return (0);
}

int			printf_handle_c(t_prt *prt)
{
	char c;

	if (prt->flag->l && !prt->flag->h)
		printf_handle_lc(prt);
	else
	{
		c = va_arg(*(prt->ap), int);
		if (prt->flag->width)
			handle_c_flags(prt, &c);
		else
		{
			if (c)
				prt->buff[prt->j] = c;
			else
				handle_zero(prt);
		}
		if (c)
			prt->j++;
	}
	return (0);
}
