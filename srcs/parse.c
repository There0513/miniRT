/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:20:04 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 22:56:37 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_add_line3(char *line, t_all *all, int i)
{
	if (line[i] == 'c' && line[i + 1] == 'y')
	{
		if (all->pars == 0)
			return (check_cy(&line[++i], all));
		return (add_cy(&line[++i], all));
	}
	else
		return (ret_error_msg("Check your .rt file, unknown element.", -1));
	return (1);
}

int	check_add_line2(char *line, t_all *all, int i)
{	
	if (line[i] == 'L')
	{
		if (all->pars == 0)
			return (check_light(&line[++i], all));
		return (add_light(&line[++i], all));
	}
	else if (line[i] == 'p' && line[i + 1] == 'l')
	{
		if (all->pars == 0)
			return (check_pl(&line[++i], all));
		return (add_pl(&line[++i], all));
	}
	else if (line[i] == 's' && line[i + 1] == 'p')
	{
		if (all->pars == 0)
			return (check_sp(&line[++i], all));
		return (add_sp(&line[++i], all));
	}
	else
		return (check_add_line3(line, all, i));
}

int	check_add_line(char *line, t_all *all)
{
	int	i;

	i = 0;
	while (ft_is_space(line[i]) == 1)
		i++;
	if (line[i] == '#')
		return (0);
	if (line[i] == '\n')
		return (0);
	if (line[i] == 'A')
	{
		if (all->pars == 0)
			return (check_ambient(&line[++i], all));
		return (add_ambient(&line[++i], all));
	}
	else if (line[i] == 'C')
	{
		if (all->pars == 0)
			return (check_camera(&line[++i], all));
		return (add_camera(&line[++i], all));
	}
	else
		return (check_add_line2(line, all, i));
}

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
				return (ret_error_msg("in check_add_line parsingadd.", -1));
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
