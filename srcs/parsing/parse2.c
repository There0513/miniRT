/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:02:14 by threiss           #+#    #+#             */
/*   Updated: 2021/09/19 21:15:38 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	parsing_check(char *file, t_all *all)
{
	int		fd;
	char	*line;

	all->pars = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, NULL, 0) < 0)
		return (ret_error_msg("Read file.", -1));
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] != 0)
		{
			if (check_add_line(line, all) == -1)
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	if (line)
		free(line);
	return (1);
}

int	parsing_add(char *file, t_all *all)
{
	int		fd;
	char	*line;

	all->pars = 1;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] != 0)
		{
			if (check_add_line(line, all) == -1)
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	if (line)
		free(line);
	return (1);
}

/*
**	3 840 × 2 160 standard '4K resolution'
*/

int	parse_rt(char *file, t_all *all)
{
	int	i;

	if (all->width > 3840)
		all->width = 3840;
	if (all->height > 2160)
		all->height = 2160;
	i = ft_strlen(file);
	if (ft_strncmp(&file[i - 3], ".rt", 3) != 0)
		return (ret_error_msg("Please use a .rt file.", -1));
	if (parsing_check(file, all) != 1)
		return (-1);
	all->sp = malloc(all->checkrt.sp * sizeof(t_sphere));
	if (!all->sp)
		return (-1);
	all->pl = malloc(all->checkrt.pl * sizeof(t_plane));
	if (!all->pl)
		return (-1);
	all->cy = malloc(all->checkrt.cy * sizeof(t_cylinder));
	if (!all->cy)
		return (-1);
	if (parsing_add(file, all) != 1)
		return (-1);
	return (1);
}
