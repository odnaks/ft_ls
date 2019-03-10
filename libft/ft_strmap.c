/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:05:06 by drestles          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*answer;
	int		n;

	if ((s == NULL) || (f == NULL))
		return (NULL);
	answer = ft_strnew((size_t)(ft_strlen(s)));
	if (!answer)
		return (NULL);
	n = 0;
	while (s[n])
	{
		answer[n] = (char)f(s[n]);
		n++;
	}
	return (answer);
}
