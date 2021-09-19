/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:16:39 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 20:00:54 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	mlx_data_init(t_mlx *mlx, int width, int height)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (-1);
	mlx->window = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->window)
		return (-1);
	mlx->img = mlx_new_image(mlx->mlx, width, height);
	if (!mlx->img)
		return (-1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->endian);
	if (!mlx->addr)
		return (-1);
	return (1);
}

void	rgb_min_max(double *r, double *g, double *b)
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

int	rgb_to_int(double r, double g, double b, t_all *all)
{
	r = r + (all->light.ambient_l * all->light.ambient_rgb.x
			* all->closest.intens);
	g = g + (all->light.ambient_l * all->light.ambient_rgb.y
			* all->closest.intens);
	b = b + (all->light.ambient_l * all->light.ambient_rgb.z
			* all->closest.intens);
	rgb_min_max(&r, &g, &b);
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->ll + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
