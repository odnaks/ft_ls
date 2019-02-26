/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:45:22 by rcotter-          #+#    #+#             */
/*   Updated: 2019/02/26 18:08:24 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flags(t_prt *prt)
{
	printf_first_flags(prt);
	printf_second_flags(prt);
	printf_third_flags(prt);
	printf_def_percentage(prt);
	printf_types(prt);
	free(prt->flag);
	return (0);
}

static int	parser(t_prt *prt)
{
	prt->i = 0;
	prt->j = 0;
	prt->len = ft_strlen(prt->format);
	prt->count_zero = 0;
	ft_bzero(prt->buff, BUFF_SIZE);
	while (prt->format[prt->i] && prt->i < (int)prt->len)
	{
		while (prt->format[prt->i] != '%' && prt->i < (int)prt->len)
		{
			prt->buff[prt->j] = prt->format[prt->i];
			prt->i++;
			prt->j++;
		}
		prt->i++;
		if (prt->format[prt->i] == '%')
			prt->buff[prt->j++] = prt->format[prt->i++];
		else if (prt->format[prt->i - 1])
			flags(prt);
	}
	ft_putstr(prt->buff);
	return (1);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_prt	prt;

	va_start(ap, format);
	prt.format = ft_strdup(format);
	prt.ap = &ap;
	if (!parser(&prt))
		return (-1);
	va_end(ap);
	free(prt.format);
	return (ft_strlen(prt.buff) + prt.count_zero);
}
