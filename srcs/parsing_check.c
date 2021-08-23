/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:18:54 by threiss           #+#    #+#             */
/*   Updated: 2021/08/23 14:17:47 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_range(float nb, float min, float max)
{
	if (nb < min || nb > max)
		return (-1);
	return (1);
}

int check_vec_range(t_vector *vec, float min, float max)
{
	if (vec->x < min || vec->x > max)
		return (-1);
	if (vec->y < min || vec->y > max)
		return (-1);
	if (vec->z < min || vec->z > max)
		return (-1);
	return (1);
}

int check_comma(char *str)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while (str[++i])
		if (str[i] == ',')
			c++;
	return (c);
}

int check_color(char *line)
{
	int i;
	char **split;
	int ret;

	ret = 0;
	i = -1;
	split = ft_split(line, ',');
	if (!ft_is_digit(line[++i]))
	{
		printf("\tcheck_color -> error here 1\n");
		ret = -1;
	}
	if (check_comma(line) != 2)
	{
		printf("\tcheck_color -> error here 2\n");
		ret = -1;
	}
	while (i < 3)
	{
		if (!ft_str_is_digit(split[i++]))
		{
			printf("\tcheck_color -> error here 3\n");
			ret = -1;
		}
	}
	t_vector tmp = create_vec(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
	if (check_vec_range(&tmp, 0.0, 255.0) == -1)
	{
		printf("\tcheck_color -> error here 4\n");
		ret = -1;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (ret);
}

int check_vec3(char *line)
{
	char **split;
	int ret;
	int i;

	ret = 0;
	i = 0;
	if (check_comma(line) != 2)
		ret = -1;
	split = ft_split(line, ','); // -50	0	20
	while (i < 3)
	{
		if (!ft_is_float(split[i]))
			ret = -1;
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (ret);
}

int add_vec3(t_vector *vec, char *line)
{
	char **split;
	int i;

	split = ft_split(line, ','); // -50	0	20
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (1);
}

int check_ambient(char *line, t_all *all)
{
	char **split;
	int ret;
	int i;

	ret = 0;
	if (all->checkrt.A)
		ret = -1;
	all->checkrt.A = 1;
	split = ft_split(line, ' ');
	if (!ft_is_float(split[0]))
	{
		printf("error here 1\n");
		ret = -1;
	}
	if (!check_range(ft_atof(split[0]), 0.0, 1.0))
	{
		printf("error here 2\n");
		ret = -1;
	}
	if (check_color(split[1]) == -1)
	{
		printf("\terror here 3\n");
		ret = -1;
	}
	i = 0; // ?
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (ret);
}

int add_ambient(char *line, t_all *all)
{
	char **split;
	char **rgb;
	int ret;
	int i;

	ret = 0;
	split = ft_split(line, ' ');
	all->light.ambient_l = ft_atof(split[0]);
	rgb = ft_split(split[1], ',');
	all->light.ambient_rgb.x = ft_atof(rgb[0]);
	all->light.ambient_rgb.y = ft_atof(rgb[1]);
	all->light.ambient_rgb.z = ft_atof(rgb[2]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (ret);
}

int check_camera(char *line, t_all *all)
{
	char **split;
	char **split2;
	int ret;

	ret = 0;
	if (all->checkrt.C)
		ret = -1;
	all->checkrt.C = 1;
	split = ft_split(line, ' ');
	check_vec3(split[0]);
	check_vec3(split[1]);
	split2 = ft_split(split[1], ',');
	t_vector tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]), ft_atof(split2[2]));
	if (check_vec_range(&tmp, -1, 1) == -1)
		ret = -1;
	if (!ft_str_is_digit(split[2])) // check fov
		ret = -1;
	if (ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 180)
		ret = -1;
	int i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	i = 0;
	while (split2[i])
		free(split2[i++]);
	free(split2);
	return (ret);
}

int add_camera(char *line, t_all *all)
{
	char **split;
	int ret;

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->camera.cam, split[0]); // cam == pov
	add_vec3(&all->camera.orient, split[1]);
	all->camera.fov = ft_atoi(split[2]) * 3.14159265 / 180;
	free(split);
	return (ret);
}

int check_light(char *line, t_all *all)
{
	char **split;
	int ret;

	ret = 0;
	if (all->checkrt.L)
		ret = -1;
	all->checkrt.L = 1;
	split = ft_split(line, ' ');
	int i = -1;
	if (check_vec3(split[0]) == -1) // all check_vec3 if =1 -> ret = -1
		ret = -1;
	// check light brightness:
	if (!ft_is_float(split[1]))
		ret = -1;
	if (ft_atof(split[1]) < 0 || ft_atof(split[1]) > 1)
		ret = -1;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (ret);
}

int add_light(char *line, t_all *all)
{
	char **split;
	int ret;

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->light.point_l, split[0]);
	all->light.bright_l = ft_atof(split[1]);
	// light_rgb = bonus
	free(split);
	return (ret);
}

int check_pl(char *line, t_all *all)
{
	char **split;
	char **split2;
	int ret;

	ret = 0;
	all->checkrt.pl++;
	split = ft_split(line, ' ');
	check_vec3(split[1]); // all check_vec3 if =1 -> ret = -1
	check_vec3(split[2]);
	split2 = ft_split(split[2], ',');
	t_vector tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]), ft_atof(split2[2]));
	if (check_vec_range(&tmp, -1, 1) == -1)
		ret = -1;
	if (!check_color(split[3]))
		ret = -1;
	free(split);
	free(split2);
	return (ret);
}

int add_pl(char *line, t_all *all)
{
	char **split;
	char **rgb;
	int ret;
	int i = all->checkrt.pl; // adapte i or i--

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->plane[i].vec, split[1]);
	add_vec3(&all->plane[i].orient, split[2]);
	rgb = ft_split(split[3], ' ');
	all->plane[i].rgb.x = ft_atof(rgb[0]);
	all->plane[i].rgb.x = ft_atof(rgb[1]);
	all->plane[i].rgb.x = ft_atof(rgb[2]);
	// free while rgb i / split i ++ ?!
	free(split);
	free(rgb);
	return (ret);
}
// coord	diameter	rgb
int check_sp(char *line, t_all *all)
{
	char **split;
	int ret;

	ret = 0;
	all->checkrt.sp++;
	split = ft_split(line, ' ');
	check_vec3(split[1]);
	if (!ft_is_float(split[2]))
		ret = -1;
	if (ft_atof(split[2]) < 0.0)
		ret = -1;
	if (!check_color(split[3]))
		ret = -1;
	free(split);
	return (ret);
}

int add_sp(char *line, t_all *all)
{
	char **split;
	char **rgb;
	int ret;
	int i = all->checkrt.sp;

	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->sphere[i].center, split[1]);
	all->sphere[i].radius = ft_atof(split[2]) / 2;
	rgb = ft_split(split[3], ' ');
	all->sphere[i].rgb.x = ft_atof(rgb[0]);
	all->sphere[i].rgb.y = ft_atof(rgb[1]);
	all->sphere[i].rgb.z = ft_atof(rgb[2]);
	// free while rgb i / split i ++ ?!
	free(split);
	free(rgb);
	return (ret);
}

int check_cy(char *line, t_all *all)
{
	char **split;
	char **split2;
	int ret;

	ret = 0;
	all->checkrt.cy++;
	split = ft_split(line, ' ');
	check_vec3(split[1]);
	split2 = ft_split(split[2], ',');
	t_vector tmp = create_vec(ft_atof(split2[0]), ft_atof(split2[1]), ft_atof(split2[2]));
	if (check_vec_range(&tmp, -1, 1) == -1)
	{
		printf("error check_cy -> 1\n");
		ret = -1;
	}
	if (!ft_is_float(split[3]))
	{
		printf("error check_cy -> 2\n");
		ret = -1;
	}
	if (ft_atof(split[3]) < 0.0)
	{
		printf("error check_cy -> 3\n");
		ret = -1;
	}
	if (!ft_is_float(split[4]))
	{
		printf("error check_cy -> 4\n");
		ret = -1;
	}
	if (ft_atof(split[4]) < 0.0)
	{
		printf("error check_cy -> 5\n");
		ret = -1;
	}
	if (check_color(split[5]) == -1)
	{
		printf("error check_cy -> 6\n");
		ret = -1;
	}
	int i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	i = 0;
	while (split2[i])
		free(split2[i++]);
	free(split2);
	return (ret);
}
// coord	orient	diameter	height	rgb
int add_cy(char *line, t_all *all)	// add_xy -> change i for all of them
{
	char **split;
	char **rgb;
	int ret;
	int i = all->checkrt.add_cy;
	
	ret = 0;
	split = ft_split(line, ' ');
	add_vec3(&all->cylinder[i].vec, split[1]);
	add_vec3(&all->cylinder[i].orient, split[2]);
	all->cylinder[i].radius = ft_atof(split[3]) / 2;
	all->cylinder[i].height = ft_atof(split[4]);
	rgb = ft_split(split[5], ',');
	all->cylinder[i].rgb.x = ft_atof(rgb[0]);
	all->cylinder[i].rgb.y = ft_atof(rgb[1]);
	all->cylinder[i].rgb.z = ft_atof(rgb[2]);
	free(split);
	free(rgb);
	all->checkrt.add_cy++;
	return (ret);
}

// if check_vec3 == -1 -> ret = -1; !!!!