/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:03:49 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int ch, size_t num)
{
	while (num > 0 && (*(char*)s2 != (char)ch))
	{
		*(char*)s1 = *(char*)s2;
		s1++;
		s2++;
		num--;
	}
	if (num == 0)
		return (NULL);
	else if (*(char*)s2 == (char)ch)
	{
		*(char*)s1 = (char)ch;
		s1++;
		return (s1);
	}
	else
		return (NULL);
}
