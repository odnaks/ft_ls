/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:34:53 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*precision_nuls(int toch, int nuls, char *digits, double o)
{
	int	i;

	i = 0;
	while (ft_strlen(ft_itoal((long int)(o * pow_10(toch) + 0.5)))
	+ i++ < (unsigned long)(toch))
		digits = ft_strjoin_left(digits, "0");
	digits = ft_strjoin_all(digits, ft_itoal((long int)(o *
		pow_10(toch) + 0.5)));
	while (nuls-- > 0)
		digits = ft_strjoin_left(digits, "0");
	return (digits);
}

static char	*precision(t_prt *prt, double d)
{
	char	*digits;
	double	o;
	int		toch;
	int		nuls;

	if (!(prt->flag->dot))
		(prt->flag->toch) = 6;
	toch = prt->flag->toch;
	nuls = 0;
	if (toch > 19)
	{
		toch = 19;
		nuls = prt->flag->toch - 19;
	}
	digits = ft_itoal((long int)d);
	digits = ft_strjoin_left(digits, ".");
	if (d >= 0.0)
		o = d - (long int)d;
	else
		o = -d + (long int)d;
	if (d < 0.0)
		prt->flag->nn = 1;
	return (precision_nuls(toch, nuls, digits, o));
}

static char	*add_nuls_for_numbers(t_prt *prt, char *digits, int sp, int d)
{
	char *free_d;

	if (d >= 0 && prt->flag->plus == 0)
		while (sp > 0)
		{
			digits = ft_strjoin_right("0", digits);
			sp--;
		}
	if (d < 0 || (prt->flag->plus == 1 && d >= 0) || (d == 0 && prt->flag->nn))
	{
		free_d = digits;
		digits = ft_strdup(&digits[1]);
		free(free_d);
		while (sp > 0)
		{
			digits = ft_strjoin_right("0", digits);
			sp--;
		}
		if (d < 0 || (d == 0 && prt->flag->nn))
			digits = ft_strjoin_right("-", digits);
		else
			digits = ft_strjoin_right("+", digits);
	}
	return (digits);
}

static char	*add_for_numbers(t_prt *prt, char *digits, int d)
{
	int	sp;

	sp = prt->flag->num - ft_strlen(digits);
	if (prt->flag->minus == 1)
		while (sp > 0)
		{
			digits = ft_strjoin_left(digits, " ");
			sp--;
		}
	else if (prt->flag->nul == 1)
		digits = add_nuls_for_numbers(prt, digits, sp, d);
	else
		while (sp > 0)
		{
			digits = ft_strjoin_right(" ", digits);
			sp--;
		}
	return (digits);
}

int			printf_handle_f(t_prt *prt)
{
	double	d;
	char	*digits;

	d = va_arg(*(prt->ap), double);
	if ((prt->flag->dot) && !(prt->flag->toch))
		digits = ft_itoal((long int)(d + 0.5));
	else
		digits = precision(prt, d);
	if ((int)d == 0 && prt->flag->nn == 1)
		digits = ft_strjoin_right("-", digits);
	if (prt->flag->plus == 1 && d >= 0)
		digits = ft_strjoin_right("+", digits);
	else if (prt->flag->space == 1 && d >= 0)
		digits = ft_strjoin_right(" ", digits);
	if (prt->flag->num > (int)ft_strlen(digits))
		digits = add_for_numbers(prt, digits, (int)d);
	while (*digits)
	{
		prt->buff[prt->j] = *digits;
		prt->j++;
		digits++;
	}
	return (0);
}
