/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:56:04 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 22:12:49 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_save_line(char **line, char **estatica, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (estatica[fd][i] != '\n' && estatica[fd][i] != '\0')
		i++;
	*line = ft_substr(estatica[fd], 0, i);
	if (estatica[fd][i] == '\n')
	{
		tmp = ft_strdup(&estatica[fd][i + 1]);
		free(estatica[fd]);
		estatica[fd] = tmp;
		if (estatica[fd][0] == '\0')
		{
			// if ()
				// free(tmp);
			free(estatica[fd]);
			estatica[fd] = NULL;
		}
	}
	else
	{
		free(estatica[fd]);
		estatica[fd] = NULL;
		return (0);
	}
	return (1);
}

int	ft_check_return(char **estatica, char **line, int r, int fd)
{
	if (r < 0)
		return (-1);
	else if (r == 0 && estatica[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (ft_save_line(line, estatica, fd));
}

int	ft_new_line_in_static(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	char		buf[1024];
	int			r;
	static char	*estatica[4096];
	char		*tmp;

	if (!line || fd < 0)
		return (-1);
	r = read(fd, buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		if (estatica[fd] == NULL)
			estatica[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(estatica[fd], buf);
			free(estatica[fd]);
			estatica[fd] = ft_strdup(tmp);
			free(tmp);
		}
		if (ft_new_line_in_static(estatica[fd]) != -1)
			break ;
		r = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_check_return(estatica, line, r, fd));
}
