/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyovano <alyovano@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 14:05:16 by alyovano          #+#    #+#             */
/*   Updated: 2019/12/09 14:05:56 by alyovano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char					*ft_scan(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

void					ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int						ft_putline(int fd, char **s, char **line)
{
	int			size;
	char		*tmp;

	size = 0;
	while (s[fd][size] != '\n')
		size++;
	if (!(*line = ft_substr(s[fd], 0, size)))
		return (-1);
	if (!(tmp = ft_strdup(&s[fd][size + 1])))
		return (-1);
	free(s[fd]);
	s[fd] = tmp;
	return (1);
}

int						output(int ret, int fd, char **str, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		ft_strdel(&str[fd]);
		return (0);
	}
	else if (ft_scan(str[fd], '\n'))
		return (ft_putline(fd, str, line));
	else
	{
		if (!(*line = ft_strdup(str[fd])))
			return (-1);
		ft_strdel(&str[fd]);
		return (0);
	}
}

int						get_next_line(int fd, char **line)
{
	int				ret;
	static char		*str[OPEN_MAX];
	char			buff[BUFFER_SIZE + 1];
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL || fd > OPEN_MAX)
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
		{
			if (!(tmp = ft_strjoin(str[fd], buff)))
				return (-1);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_scan(str[fd], '\n'))
			break ;
	}
	return (output(ret, fd, str, line));
}
