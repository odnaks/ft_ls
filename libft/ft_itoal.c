/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:49:07 by drestles          #+#    #+#             */
/*   Updated: 2019/02/26 18:08:24 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_pow(size_t a, long int n)
{
	while (n--)
		a = a * 10;
	return (a);
}

static	size_t		ft_neg1(long int n, size_t i)
{
	if (n < 0)
		i = i + 1;
	return (i);
}

static	size_t		ft_neg2(long int n, size_t i)
{
	if (n < 0)
		i = i - 1;
	return (i);
}

static	long int	ft_neg3(long int n)
{
	if (n < 0)
		n = n * (-1);
	return (n);
}

char				*ft_itoal(long int n)
{
	size_t		j;
	size_t		i;
	long int	num;
	char		*s;

	i = 0;
	j = 0;
	num = n;
	while ((num = num / 10))
		i++;
	i = ft_neg1(n, i);
	if (!(s = (char *)(malloc(sizeof(char) * (i + 2)))))
		return (NULL);
	i = ft_neg2(n, i) + 1;
	if (n < 0)
		s[j++] = '-';
	if (n == -2147483648 && (s[j++] = '2') && (i--))
		n = 147483648;
	n = ft_neg3(n);
	while (--i && (s[j++] = (n / ft_pow(10, i - 1)) + '0'))
		n = n % ft_pow(10, i - 1);
	s[j] = n + '0';
	s[j + 1] = '\0';
	return (s);
}
