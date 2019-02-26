/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:38:32 by rcotter-          #+#    #+#             */
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

static int	handle_null(t_prt *prt, char *s, int *ms)
{
	int len;

	if (ms && !(*ms))
		return (0);
	s = "(null)";
	len = ft_strlen(s);
	if (!prt->flag->dot)
		prt->flag->toch = ((size_t)prt->flag->num
		< (unsigned long)len) ? len : prt->flag->num;
	if (prt->flag->width)
		handle_s_flags(prt, s, len);
	else
		while (*s && prt->flag->toch--)
			(prt->buff[prt->j++]) = *s++;
	return (0);
}

static int	handle_ls_flags(t_prt *prt, char *s, size_t len)
{
	if (!prt->flag->dot)
		prt->flag->toch = ((size_t)prt->flag->num < len) ? len : prt->flag->num;
	if (prt->flag->width && ((size_t)prt->flag->num > len ||
		prt->flag->num > prt->flag->toch) && !prt->flag->minus)
	{
		prt->flag->num -= ((size_t)prt->flag->toch
		> len) ? len : prt->flag->toch;
		while (prt->flag->num--)
			prt->buff[prt->j++] = ' ';
		while (*s && prt->flag->toch--)
			(prt->buff[prt->j++]) = *s++;
	}
	else
	{
		prt->flag->num -= ((size_t)prt->flag->toch
		> len) ? len : prt->flag->toch;
		while (*s && prt->flag->toch--)
			(prt->buff[prt->j++]) = *s++;
		if (prt->flag->num > 0)
			while (prt->flag->num--)
				prt->buff[prt->j++] = ' ';
	}
	return (0);
}

int			printf_handle_ls(t_prt *prt)
{
	int		*ms;
	char	*s;
	char	tmp[BUFF_SIZE];
	int		index;
	char	*old;

	s = NULL;
	index = 0;
	if (prt->flag->h)
		printf_handle_ls(prt);
	else
	{
		if (!(ms = va_arg(*(prt->ap), int *)) || !(*ms))
			return (handle_null(prt, s, ms));
		while (*ms++)
		{
			s = printf_unicode(*ms);
			old = s;
			while (*s)
				(tmp[index++]) = *s++;
			free(old);
		}
		handle_ls_flags(prt, tmp, ft_strlen(tmp));
	}
	return (0);
}
