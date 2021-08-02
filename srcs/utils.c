/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:16:39 by threiss           #+#    #+#             */
/*   Updated: 2021/05/21 17:58:07 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	mlx_data_init(t_mlx *data, int width, int height)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, width, height, "miniRT");
	data->img = mlx_new_image(data->mlx, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->endian);
}

int		rgb_to_int(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	getNorm2(t_vector *sphere)
{
	return (sphere->x * sphere->x + sphere->y * sphere->y + sphere->z * sphere->z);
}

void	normalize(t_vector *sphere)
{
	double	norm = sqrt(getNorm2(sphere));	// = magnitude(Laenge) of Vector
	sphere->x /= norm;
	sphere->y /= norm;
	sphere->z /= norm;
}
//RAY = r(origine(=vector/point), direction(=vector))

t_vector get_normalized(t_vector a)
{
	normalize(&a);
	return (a);
}

t_vector	add_min_operation(char sign, t_vector a, t_vector b)
{
	t_vector	new_vector;

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

t_vector	mult_operation(char sign, double nbr, t_vector a)
{
	t_vector	new_vector;

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

t_vector	create_vec(double x, double y, double z)
{
	t_vector	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}