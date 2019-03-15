/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 03:12:51 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *a, const char *b)
{
	size_t	i;
	size_t	j;
	size_t	n;

	n = ft_strlen(b);
	i = 0;
	if (*b == '\0')
		return ((char*)a);
	while (a[i])
	{
		j = 0;
		while (a[i] && a[i] == b[j])
		{
			i++;
			j++;
		}
		if (j == n)
			return (&(((char*)a)[i - n]));
		else
			i -= j;
		i++;
	}
	return (NULL);
}
