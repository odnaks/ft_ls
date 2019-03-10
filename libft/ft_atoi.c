/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:03:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long	flag;
	long long	an;

	flag = 1;
	an = 0;
	while ((*str == '\n') || (*str == '\t') || (*str == '\v')
			|| (*str == ' ') || (*str == '\r') || (*str == '\f'))
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '-' || (*str == '+'))
		str++;
	while (*str == '0')
		str++;
	while (*str && (*str >= '0') && (*str <= '9'))
	{
		if (an < 0 && ((an * 10 + 48 - *str) < 0))
			an = (an * 10 + 48 - *str++);
		else if (an >= 0 && ((an * 10 - 48 + *str) >= 0))
			an = (an * 10 - 48 + *str++) * flag;
		else
			return (-1 * (an > 0));
		flag = 1;
	}
	return ((int)an);
}
