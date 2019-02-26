/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:24:58 by rcotter-          #+#    #+#             */
/*   Updated: 2019/02/26 18:08:24 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_s_flags(t_prt *prt, char *s, size_t len)
{
	prt->flag->num -= ((size_t)prt->flag->toch > len) ? len : prt->flag->toch;
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

int			printf_handle_s(t_prt *prt)
{
	char	*s;
	size_t	len;

	if (prt->flag->l && !prt->flag->h)
		printf_handle_ls(prt);
	else
	{
		s = va_arg(*(prt->ap), char *);
		if (s == 0)
			s = "(null)";
		len = ft_strlen(s);
		if (!prt->flag->dot)
			prt->flag->toch = ((size_t)prt->flag->num
			< len) ? len : prt->flag->num;
		if (prt->flag->width && ((size_t)prt->flag->num > len
		|| prt->flag->num > prt->flag->toch))
			handle_s_flags(prt, s, len);
		else
			while (*s && prt->flag->toch--)
				(prt->buff[prt->j++]) = *s++;
	}
	return (0);
}
