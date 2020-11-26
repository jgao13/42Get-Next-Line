/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:36:59 by jgao              #+#    #+#             */
/*   Updated: 2020/11/26 13:49:59 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #include <stdio.h>
// #include <unistd.h>

// #include <limits.h>

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }


// void	ft_putnbr(int nb)
// {
// 	if (nb == INT_MIN)
// 	{
// 		ft_putchar('-');
// 		ft_putnbr(nb / -10);
// 	}
// 	if (nb < 0 && nb != INT_MIN)
// 	{
// 		ft_putchar('-');
// 		nb = -nb;
// 	}
// 	if (nb / 10 != 0 && nb != INT_MIN)
// 		ft_putnbr(nb / 10);
// 	if (nb == INT_MIN)
// 		ft_putchar((nb % 10 * -1) + '0');
// 	else
// 		ft_putchar(nb % 10 + '0');
// }


// void	ft_putstr(char *s)
// {
// 	write(1, s, ft_strlen(s));
// }

int			clearbuffer(char *buffer)
{
	int	i;
	int	u;
	int	ret;

	i = 0;
	u = 0;
	while (buffer[i] != '\n' && buffer[i])
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
		return(-2);
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

int	get_next_line(int fd, char **line)
{
	int				readret;
	int				ret;
	static char		buffer[256][BUFFER_SIZE + 1];

	ret = 0;
	readret = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer[fd], 0) < 0)
		return (-1);
	*line = NULL;
	while (readret > 0 && ret != 1)
	{
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

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int	main(int ac, char **av)
// {
// 	char	*str = NULL;
// 	int		fd[ac];
// 	int		ret = 1;
// 	int		i = 1;

// 	if (ac < 1)
// 		return (0);
// 	while (i < ac)
// 	{
// 		printf("File name = %s\n", av[i]);
// 		if ((fd[i] = open(av[i], O_RDONLY)) < 0)
// 			return (0);
// 		while (ret > 0)
// 		{
// 			ret = get_next_line(fd[i], &str);
// 			printf("ret = %d, str = %s\n", ret, str);
// 			usleep(20000);
// 		}
// 		close(fd[i]);
// 		ret = 1;
// 		i++;
// 	}
// 	free(str);
// 	return (0);
// }