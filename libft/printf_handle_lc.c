/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_lc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:38:32 by rcotter-          #+#    #+#             */
/*   Updated: 2019/02/26 18:08:24 by pcollio-         ###   ########.fr       */
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

static int	handle_lc_flags(t_prt *prt, char *s, size_t len)
{
	prt->flag->num -= ((size_t)prt->flag->toch
	> (unsigned long)len) ? len : prt->flag->toch;
	if (prt->flag->minus)
	{
		while (*s && prt->flag->toch--)
			(prt->buff[prt->j++]) = *s++;
		while (prt->flag->num--)
			prt->buff[prt->j++] = ' ';
	}
	else
	{
		while (prt->flag->num--)
			prt->buff[prt->j++] = ' ';
		while (*s && prt->flag->toch--)
			(prt->buff[prt->j++]) = *s++;
	}
	return (0);
}

int			printf_handle_lc(t_prt *prt)
{
	int		c;
	char	*s;
	int		len;
	char	*s_temp;

	if (prt->flag->h)
		printf_handle_c(prt);
	else
	{
		c = va_arg(*(prt->ap), int);
		if (c == 0)
			handle_zero(prt);
		s = printf_unicode(c);
		s_temp = s;
		len = ft_strlen(s);
		if (!prt->flag->dot)
			prt->flag->toch = (prt->flag->num < len) ? len : prt->flag->num;
		if (prt->flag->width && prt->flag->num > len)
			handle_lc_flags(prt, s, len);
		else
			while (*s && prt->flag->toch--)
				(prt->buff[prt->j++]) = *s++;
		free(s_temp);
	}
	return (0);
}
