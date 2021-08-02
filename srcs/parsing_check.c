/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:18:54 by threiss           #+#    #+#             */
/*   Updated: 2021/08/02 15:17:22 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//______________________________________________new file

int	check_range(float nb, float min, float max)
{
	if (nb < min || nb > max)
		return (-1);
	return (1);
}

int	check_vec_range(t_vector *vec, float min, float max)
{
	if (vec->x < min || vec->x > max)
		return (-1);
	if (vec->y < min || vec->y > max)
	{
		printf("error min max y\n");
		return (-1);
	}
	if (vec->z < min || vec->z > max)
		return (-1);
	return (1);
}

int	check_comma(char *str)
{
	int	i;
	int	c;

	i = -1	;
	c = 0;
	while (str[++i])
		if (str[i] == ',')
			c++;
	return (c);
}

int ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_add_color(char *line, t_vector *rgb)
{
	int		i;
	char	**split;

	i = -1;
	if (!ft_is_digit(line[++i]))
		return (-1);
	if (check_comma(line) != 2)
		return (-1);
	split = ft_split(line, ',');
	while (i < 3)
		if (!ft_str_is_digit(split[i++]))
			return (-1); 	// error message not digit
	rgb->x = ft_atof(split[0]);
	rgb->y = ft_atof(split[1]);
	rgb->z = ft_atof(split[2]);
	if (check_vec_range(rgb, 0.0, 255.0) == -1)
			return (-1); 	// error message not digit
	return (1);
}

int	check_add_vec3(t_vector *cam, char *line)	// point of view
{
	char	**split;
	int		i;

	i = 0;
	if (check_comma(line) != 2)
		return (-1);
	split = ft_split(line, ',');	// -50	0	20
	while (i < 3)
		if (!ft_is_float(split[i++]))
			return (-1);
	cam->x = ft_atof(split[0]);
	cam->y = ft_atof(split[1]);
	cam->z = ft_atof(split[2]);
	return (1);
}

int	check_add_fov(double *fov, char *line)
{
	if (!ft_str_is_digit(line))
		return (-1);
	*fov = ft_atoi(line);
	if (*fov < 0 || *fov > 180)
		return (-1);
	*fov = *fov * 3.14159265 / 180;
	return (1);
}

int ft_str_is_digit(char *str)
{
	int		i;

	i = -1;
	if (str[++i] == '-')
		i++;
	while (i < ft_strlen(str))
		if (!ft_is_digit(str[i++]))
			return (0);
	return (1);
}

int ft_is_float(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_is_digit(str[i]))
		i++;
	if (i == 0)
		return (0);
	return (1);
}

float	ft_atof(char *str)
{
	float	nb;
	int		i;
	float	neg;
	float	div;

	nb = 0.0;
	i = 0;
	neg = 1;
	div = 0.1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (str[i] == '.')
	{
		while (str[++i] >= '0' && str[i] <= '9')
		{
			nb = nb + (div * (str[i] - 48));
			div *= 0.1;
		}
	}
	return (nb * neg);
}

//______________________________________________new file

int check_add_ambient(char *line, t_all *all)
{
	char	**split;

	if (all->checkrt.A)
	{
		printf("error in check_add_ambient checkrt.A already exist\n");
		return (-1);	// error message double declaration of A
	}
	all->checkrt.A = 1;
	split = ft_split(line, ' ');
	if (!ft_is_float(split[0]))
	{
		printf("error in check_add_ambient is not float\n");
		return (-1);
	}
	all->light.ambient_l = ft_atof(split[0]);
	if (!check_range(all->light.ambient_l, 0.0, 1.0))
	{
		printf("Error in check_add_ambient !check_range\n");
		return (-1);
	}
	if (!check_add_color(split[1], &all->light.ambient_rgb))
	{
		printf("Error in check_add_ambient !check_add_color\n");
		return (-1);
	}
	return (1);
}

int	check_add_camera(char *line, t_all *all)
{
	char	**split;

	if (all->checkrt.C)
		return (-1);	// error message double declaration of C
	all->checkrt.C = 1;
	split = ft_split(line, ' ');
	if (!check_add_vec3(&all->camera.cam, split[0]))	// cam == pov
		return (-1);
	if (!check_add_vec3(&all->camera.orient, split[1]))
		return (-1);
	if (check_vec_range(&all->camera.orient, -1.0, 1.0) == -1)
		return (-1);
	if (!check_add_fov(&all->camera.fov, split[2]))
		return (-1);
	return (1);
}

int	check_add_light(char *line, t_all *all)
{
	char	**split;

	if (all->checkrt.L)
	{
		printf("L already declared!\n");
		return (-1);	// error message double declaration of XY
	}
	all->checkrt.L = 1;
	split = ft_split(line, ' ');
	if (!check_add_vec3(&all->light.point_l, split[0]))
		return (-1);
	if (!ft_is_float(split[1]))
		return (-1);
	all->light.bright_l = ft_atof(split[1]);
	if (!check_range(all->light.bright_l, 0.0, 1.0))
		return (-1);
	// light_rgb = bonus
	return (1);
}

int	check_add_pl(char *line, t_all *all)
{
	char	**split;

	all->checkrt.pl++;
	split = ft_split(line, ' ');
	if (!check_add_vec3(&all->plane.vec, split[1]))
		return (-1);
	if (!check_add_vec3(&all->plane.orient, split[2]))
		return (-1);
	if (check_vec_range(&all->plane.orient, -1.0, 1.0) == -1)
	{
		printf("error range orient vec\n");
		return (-1);
	}
	if (check_add_color(split[3], &all->plane.rgb) == -1)
		return (-1);
	return (1);
}

int	check_add_sp(char *line, t_all *all)
{
	char	**split;
	int		i = all->checkrt.sp;

	all->checkrt.sp++;
	split = ft_split(line, ' ');
	if (!check_add_vec3(&all->sphere[i].center, split[1]))
		return (-1);
	if (!ft_is_float(split[2]))
		return (-1);
	all->sphere[i].radius = ft_atof(split[2]) / 2;
	if (all->sphere[i].radius < 0)
		return (-1);
	if (!check_add_color(split[3], &all->sphere[i].rgb))
		return (-1);
	return (1);
}

int	check_add_cy(char *line, t_all *all)
{
	char	**split;

	all->checkrt.cy++;
	split = ft_split(line, ' ');
	if (!check_add_vec3(&all->cylinder.vec, split[1]))
		return (-1);
	if (!check_add_vec3(&all->cylinder.orient, split[2]))
		return (-1);
	if (check_vec_range(&all->cylinder.orient, -1.0, 1.0) == -1)
		return (-1);
	if (!ft_is_float(split[3]))
		return (-1);
	all->cylinder.radius = ft_atof(split[3]) / 2;
	if (all->cylinder.radius < 0)
		return (-1);
	if (!ft_is_float(split[4]))
		return (-1);
	all->cylinder.height = ft_atof(split[4]);
	if (all->cylinder.height < 0)
		return (-1);
	if (!check_add_color(split[5], &all->cylinder.rgb))
		return (-1);
	return (1);
}
