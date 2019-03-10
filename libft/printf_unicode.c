/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:42:28 by rcotter-          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*multibytes(char *uni, int c, int bytes)
{
	int marker;

	if (bytes == 2)
		marker = 192;
	else if (bytes == 3)
		marker = 224;
	else if (bytes == 4)
		marker = 240;
	uni = (char *)malloc(sizeof(char) * (bytes + 1));
	uni[bytes--] = '\0';
	while (bytes > 0)
	{
		uni[bytes--] = 128 | (c & 63);
		c = c >> 6;
	}
	uni[bytes] = marker | (c & 63);
	return (uni);
}

char		*printf_unicode(int c)
{
	char	*uni;
	int		i;

	i = 0;
	if (c >= 0 && c <= 127)
	{
		uni = (char *)malloc(sizeof(char) * 2);
		uni[i++] = c;
		uni[i] = '\0';
		return (uni);
	}
	else if (c >= 128 && c <= 2047)
		i = 2;
	else if (c >= 2048 && c <= 65535)
		i = 3;
	else if (c >= 65536 && c <= 1114111)
		i = 4;
	uni = NULL;
	uni = multibytes(uni, c, i);
	return (uni);
}
