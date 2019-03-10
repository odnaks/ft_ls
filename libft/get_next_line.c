/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 03:15:50 by drestles          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:28 by pcollio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	out_lines(char **line, char *reader)
{
	char *s;

	s = ft_strchr(reader, '\n');
	if (s)
	{
		s[0] = '\0';
		*line = ft_strdup(reader);
		ft_memmove(reader, &s[1], ft_strlen(&s[1]) + 1);
		return (1);
	}
	else if (ft_strlen(reader) > 0)
	{
		*line = ft_strdup(reader);
		*reader = 0;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*reader[MAX_FD];
	char		buffer[BUFF_SIZE_GNL + 1];
	int			size;
	char		*temp;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (!reader[fd] && !(reader[fd] = ft_strnew(1)))
		return (-1);
	while (!ft_strchr(reader[fd], '\n'))
	{
		if ((size = read(fd, buffer, BUFF_SIZE_GNL)) == -1)
			return (-1);
		if (size == 0)
			break ;
		buffer[size] = '\0';
		temp = ft_strjoin(reader[fd], buffer);
		free(reader[fd]);
		reader[fd] = temp;
	}
	return (out_lines(line, reader[fd]));
}
