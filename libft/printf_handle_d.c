/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:34:59 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*add_nuls_for_numbers(t_prt *prt,
	char *digits, int sp, long int d)
{
	if (d >= 0 && prt->flag->plus == 0 && prt->flag->space == 0)
		while (sp > 0)
		{
			digits = ft_strjoin_right("0", digits);
			sp--;
		}
	if (d < 0 || (prt->flag->plus == 1 && d >= 0) ||
		(prt->flag->space == 1 && d >= 0))
	{
		digits = ft_strdup(&digits[1]);
		while (sp > 0)
		{
			digits = ft_strjoin_right("0", digits);
			sp--;
		}
		if (d < 0)
			digits = ft_strjoin_right("-", digits);
		else if (prt->flag->plus == 1 && d >= 0)
			digits = ft_strjoin_right("+", digits);
		else
			digits = ft_strjoin_right(" ", digits);
	}
	return (digits);
}

static char		*add_for_numbers(t_prt *prt, char *digits, long int d)
{
	int sp;

	sp = prt->flag->num - ft_strlen(digits);
	if (prt->flag->minus == 1)
		while (sp > 0)
		{
			digits = ft_strjoin_left(digits, " ");
			sp--;
		}
	else if (prt->flag->nul == 1 && prt->flag->dot == 0)
		digits = add_nuls_for_numbers(prt, digits, sp, d);
	else
		while (sp > 0)
		{
			digits = ft_strjoin_right(" ", digits);
			sp--;
		}
	return (digits);
}

static long int	assignment(t_prt *prt)
{
	long int ld;

	if (prt->flag->h == 1)
		ld = (long int)(short int)va_arg(*(prt->ap), int);
	else if (prt->flag->hh == 1)
		ld = (long int)(char)va_arg(*(prt->ap), int);
	else if (prt->flag->l == 1)
		ld = (long int)va_arg(*(prt->ap), long);
	else if (prt->flag->ll == 1)
		ld = (long int)va_arg(*(prt->ap), long long);
	else
		ld = (long int)va_arg(*(prt->ap), int);
	return (ld);
}

static char		*precision(t_prt *prt, char *digits, long int ld_a)
{
	if (!(prt->flag->toch == 0 && prt->flag->dot == 1 && ld_a == 0))
	{
		if (ld_a < -9223372036854775807)
			digits = ft_strdup("9223372036854775808");
		else
			digits = ft_itoal(ld_a);
	}
	else
		digits = ft_strnew(0);
	while ((int)ft_strlen(digits) < prt->flag->toch)
		digits = ft_strjoin_right("0", digits);
	return (digits);
}

int				printf_handle_d(t_prt *prt)
{
	long int			ld;
	long int			ld_a;
	char				*digits;
	char				*free_digits;

	ld = assignment(prt);
	if (ld < -9223372036854775807)
		ld_a = ld;
	else
		ld_a = abs_l(ld);
	digits = NULL;
	digits = precision(prt, digits, ld_a);
	if (ld < 0)
		digits = ft_strjoin_right("-", digits);
	if (prt->flag->plus == 1 && ld >= 0)
		digits = ft_strjoin_right("+", digits);
	else if (prt->flag->space == 1 && ld >= 0)
		digits = ft_strjoin_right(" ", digits);
	if (prt->flag->num > (int)ft_strlen(digits))
		digits = add_for_numbers(prt, digits, (long int)ld);
	free_digits = digits;
	while (*digits)
		(prt->buff[prt->j++]) = *digits++;
	free(free_digits);
	return (0);
}
