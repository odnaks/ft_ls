/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:34:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add_nuls_for_numbers(char *digits, int sp)
{
	while (sp > 0)
	{
		digits = ft_strjoin_right("0", digits);
		sp--;
	}
	return (digits);
}

static char	*add_for_numbers(t_prt *prt, char *digits)
{
	int	sp;

	sp = prt->flag->num - ft_strlen(digits);
	if (prt->flag->minus == 1)
		while (sp > 0)
		{
			digits = ft_strjoin_left(digits, " ");
			sp--;
		}
	else if (prt->flag->nul == 1 && !(prt->flag->toch == 0
	&& prt->flag->dot == 1))
		digits = add_nuls_for_numbers(digits, sp);
	else
		while (sp > 0)
		{
			digits = ft_strjoin_right(" ", digits);
			sp--;
		}
	return (digits);
}

long int	assignment_u(t_prt *prt)
{
	unsigned long int	ld;

	if (prt->flag->h == 1)
		ld = (unsigned long int)(unsigned short int)va_arg(*(prt->ap),
		unsigned int);
	else if (prt->flag->hh == 1)
		ld = (unsigned long int)(unsigned char)va_arg(*(prt->ap), unsigned int);
	else if (prt->flag->l == 1 || prt->flag->ll == 1)
		ld = (unsigned long int)va_arg(*(prt->ap), unsigned long int);
	else
		ld = (unsigned long int)va_arg(*(prt->ap), unsigned int);
	return (ld);
}

static char	*precision(t_prt *prt, char *digits, unsigned long int ld_a)
{
	if (!(prt->flag->toch == 0 && prt->flag->dot == 1 && ld_a == 0))
		digits = ft_itoal_u(ld_a);
	else
		digits = ft_strnew(0);
	while (ft_strlen(digits) < (size_t)prt->flag->toch)
		digits = ft_strjoin_right("0", digits);
	return (digits);
}

int			printf_handle_u(t_prt *prt)
{
	unsigned long int	ld;
	char				*digits;
	char				*free_digits;

	ld = assignment_u(prt);
	digits = NULL;
	digits = precision(prt, digits, ld);
	if ((size_t)prt->flag->num > ft_strlen(digits))
		digits = add_for_numbers(prt, digits);
	free_digits = digits;
	while (*digits)
	{
		(prt->buff[prt->j]) = *digits;
		prt->j++;
		digits++;
	}
	free(free_digits);
	return (0);
}
