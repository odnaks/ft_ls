/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 03:12:51 by drestles          #+#    #+#             */
/*   Updated: 2019/03/14 17:34:21 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;

	if ((!*str && !*to_find) || !*to_find)
		return ((char *)str);
	if (ft_strlen(to_find) > len)
		return (NULL);
	i = 0;
	while (*str != '\0' && i <= len)
	{
		if (ft_strncmp(str, to_find, ft_strlen(to_find)) == 0)
			if ((len - i) >= ft_strlen(to_find))
				return ((char *)str);
		str++;
		i++;
	}
	if (i == len && *str)
		return ((char *)str);
	return (NULL);
}
