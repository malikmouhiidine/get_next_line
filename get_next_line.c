/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:19:10 by mmouhiid          #+#    #+#             */
/*   Updated: 2023/11/22 21:33:07 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*read_handler(int fd, char *line)
{
	ssize_t		ret;
	char		buffer[BUFFER_SIZE + 1];

	ret = read(fd, buffer, BUFFER_SIZE);
	buffer[ret] = '\0';
	line = ft_strjoin(line, buffer);
	while (!ft_strchr(line, '\n') && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (remainder)
		line = ft_strdup(remainder);
	else
		line = ft_strdup("");
	line = read_handler(fd, line);
	if (ft_strchr(line, '\n'))
	{
		if (ft_strchr(line, '\n') - line < (long)ft_strlen(line))
			remainder = ft_strdup(ft_strchr(line, '\n') + 1);
		else
			remainder = NULL;
		line = ft_substr(line, 0, ft_strchr(line, '\n') + 1 - line);
	}
	if (!ft_strlen(line))
		return (NULL);
	return (line);
}
