/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:21:40 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 19:29:56 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	add_vec3(t_vector *vec, char *line)
{
	char	**split;

	split = ft_split(line, ',');
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	free_all(split);
	return (1);
}

int	add_ambient(char *line, t_all *all)
{
	char	**split;
	char	**rgb;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	all->light.ambient_l = ft_atof(split[0]);
	rgb = ft_split(split[1], ',');
	all->light.ambient_rgb.x = ft_atof(rgb[0]);
	all->light.ambient_rgb.y = ft_atof(rgb[1]);
	all->light.ambient_rgb.z = ft_atof(rgb[2]);
	free_all(split);
	free_all(rgb);
	return (ret);
}

int	add_camera(char *line, t_all *all)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->camera.cam, split[0]);
	add_vec3(&all->camera.orient, split[1]);
	all->camera.fov = ft_atoi(split[2]) * 3.14159265 / 180;
	free_all(split);
	return (ret);
}

int	add_light(char *line, t_all *all)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->light.point_l, split[0]);
	all->light.bright_l = ft_atof(split[1]);
	free_all(split);
	return (ret);
}
