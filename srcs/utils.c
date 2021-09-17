/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:16:39 by threiss           #+#    #+#             */
/*   Updated: 2021/08/27 15:02:31 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int mlx_data_init(t_mlx *data, int width, int height)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	data->window = mlx_new_window(data->mlx, width, height, "miniRT");
	if (!data->window)
		return (-1);
	data->img = mlx_new_image(data->mlx, width, height);
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->endian);
	if (!data->addr)
		return (-1);
	return (1);
}

void rgb_min_max(double *r, double *g, double *b)
{
	if (*r < 0.0)
		*r = 0.0;
	if (*g < 0.0)
		*g = 0.0;
	if (*b < 0.0)
		*b = 0.0;
	if (*r > 255.0)
		*r = 255.0;
	if (*g > 255.0)
		*g = 255.0;
	if (*b > 255.0)
		*b = 255.0;
}

int rgb_to_int(double r, double g, double b, t_all *all)
{
	r = r + (all->light.ambient_l * all->light.ambient_rgb.x * all->closest.intens);
	g = g + (all->light.ambient_l * all->light.ambient_rgb.y * all->closest.intens);
	b = b + (all->light.ambient_l * all->light.ambient_rgb.z * all->closest.intens);
	rgb_min_max(&r, &g, &b);
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

double dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double getNorm2(t_vector *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

/*
**	sqrt(getNorm2(vec)) = magnitude (length) of vector
*/

void normalize(t_vector *vec)
{
	double norm;

	norm = sqrt(getNorm2(vec));
	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

t_vector get_normalized(t_vector a)
{
	normalize(&a);
	return (a);
}

t_vector calc_op(char sign, t_vector a, t_vector b)
{
	t_vector new_vector;

	new_vector.x = 0;
	new_vector.y = 0;
	new_vector.z = 0;
	if (sign == '+')
	{
		new_vector.x = a.x + b.x;
		new_vector.y = a.y + b.y;
		new_vector.z = a.z + b.z;
	}
	else if (sign == '-')
	{
		new_vector.x = a.x - b.x;
		new_vector.y = a.y - b.y;
		new_vector.z = a.z - b.z;
	}
	return (new_vector);
}

t_vector mult_op(char sign, double nbr, t_vector a)
{
	t_vector new_vector;

	new_vector.x = 0;
	new_vector.y = 0;
	new_vector.z = 0;
	if (sign == '*')
	{
		new_vector.x = nbr * a.x;
		new_vector.y = nbr * a.y;
		new_vector.z = nbr * a.z;
	}
	return (new_vector);
}

t_vector create_vec(double x, double y, double z)
{
	t_vector new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}
