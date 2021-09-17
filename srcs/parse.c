/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:20:04 by threiss           #+#    #+#             */
/*   Updated: 2021/08/23 17:31:23 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_add_line(char *line, t_all *all) // add struct
{
	int i;

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
	else if (line[i] == 'L')
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
	else if (line[i] == 'c' && line[i + 1] == 'y')
	{
		if (all->pars == 0)
			return (check_cy(&line[++i], all));
		return (add_cy(&line[++i], all));
	}
	else
	{
		printf("Error\nCheck your .rt file, unknown element.");
		return (-1);
	}
	return (1);
}

int parsing_check(char *file, t_all *all)
{
	int fd;
	char *line;
	int i;

	all->pars = 0;
	i = ft_strlen(file);
	if (ft_strncmp(&file[i - 3], ".rt", 3) != 0)
	{
		printf("Error\nPlease use a .rt file\n");
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, NULL, 0) < 0)
	{
		printf("Error\nRead file\n");
		return (0);
	}
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

int parsing_add(char *file, t_all *all) // update after parsing_check
{
	int fd;
	char *line;

	all->pars = 1;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] != 0)
		{
			if (check_add_line(line, all) == -1)
			{
				printf("Error\nin check_add_line parsingadd\n");
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

// 3 840 × 2 160 standard '4K resolution'
int parse_rt(char *file, t_all *all)
{
	if (all->width > 3840)
		all->width = 3840;
	if (all->height > 2160)
		all->height = 2160;
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
	return (1); // if everything is ok -> ret 1
}