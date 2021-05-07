/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:18:33 by ahmcherk          #+#    #+#             */
/*   Updated: 2019/11/13 14:25:39 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	line_manager(char **str, char **line, int fd)
{
	char	*temp;

	if (!ft_strchr(str[fd], '\n') && ft_strchr(str[fd], '\0') &&
			str[fd] != NULL)
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	else
	{
		*line = ft_strsub(str[fd], 0, ft_strchr(str[fd], '\n') - (&str[fd][0]));
		temp = ft_strsub(str[fd], (ft_strchr(str[fd], '\n') - &str[fd][0]) + 1,
				(&str[fd][ft_strlen(str[fd])] - ft_strchr(str[fd], '\n')));
		ft_strdel(&str[fd]);
		str[fd] = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int				ret_read;
	char			buffer[BUFF_SIZE + 1];
	static char		*str[4864];
	char			*p;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || fd > 4096)
		return (-1);
	while ((ret_read = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (str[fd] == NULL)
			str[fd] = ft_strnew(0);
		buffer[ret_read] = '\0';
		p = str[fd];
		str[fd] = ft_strjoin(str[fd], buffer);
		ft_strdel(&p);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ret_read < 0)
		return (-1);
	if (ret_read == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	return (line_manager(str, line, fd));
}
