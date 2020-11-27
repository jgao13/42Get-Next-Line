/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:36:59 by jgao              #+#    #+#             */
/*   Updated: 2020/11/27 12:22:01 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	clearbuffer(char *buffer)
{
	int	i;
	int	u;
	int	ret;

	i = 0;
	u = 0;
	while (buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		ret = 1;
	else
		ret = 0;
	if (i++ > 0 || buffer[0] == '\n')
	{
		while (buffer[i])
			buffer[u++] = buffer[i++];
		buffer[u] = '\0';
	}
	return (ret);
}

static int	readbuffer(char *buffer, char **line)
{
	size_t	blen;
	size_t	llen;

	if (!buffer)
		return (-1);
	blen = custom_strlen(buffer);
	if (!(*line = ft_realloc(*line, blen)))
		return (-2);
	llen = ft_strlen(*line);
	ft_memmove(*line + llen, buffer, blen);
	(*line)[llen + blen] = '\0';
	if (!buffer[blen])
	{
		buffer[0] = '\0';
		return (-1);
	}
	return (clearbuffer(buffer));
}

int			get_next_line(int fd, char **line)
{
	int				readret;
	int				ret;
	static char		buffer[256][BUFFER_SIZE + 1];

	ret = 0;
	readret = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer[fd], 0) < 0 || !line)
		return (-1);
	*line = NULL;
	while (readret > 0 && ret != 1)
	{
		if (readret > 0)
			if ((ret = readbuffer(buffer[fd], line)) == -1)
			{
				if ((readret = read(fd, buffer[fd], BUFFER_SIZE)) < 0)
					return (-1);
				buffer[fd][readret] = '\0';
			}
		if (ret == -2)
			return (-1);
	}
	if (readret > 0)
		return (1);
	return (0);
}
