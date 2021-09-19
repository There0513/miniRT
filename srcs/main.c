/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:09:49 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 22:07:13 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	get_color(char *nearest, t_all *all, double intens)
{
	int	i;

	i = nearest[2] - 48;
	if (nearest[0] == 's' && nearest[1] == 'p')
		return (rgb_to_int(all->sp[i].rgb.x * intens + all->sp[i].rgb.x * 0.3,
				all->sp[i].rgb.y * intens + all->sp[i].rgb.y * 0.3,
				all->sp[i].rgb.z * intens + all->sp[i].rgb.z * 0.3, all));
	if (nearest[0] == 'p' && nearest[1] == 'l')
		return (rgb_to_int(all->pl[i].rgb.x * intens + all->pl[i].rgb.x * 0.3,
				all->pl[i].rgb.y * intens + all->pl[i].rgb.y * 0.3,
				all->pl[i].rgb.z * intens + all->pl[i].rgb.z * 0.3, all));
	if (nearest[0] == 'c' && nearest[1] == 'y')
		return (rgb_to_int(all->cy[i].rgb.x * intens + all->cy[i].rgb.x * 0.3,
				all->cy[i].rgb.y * intens + all->cy[i].rgb.y * 0.3,
				all->cy[i].rgb.z * intens + all->cy[i].rgb.z * 0.3, all));
	return (16777215);
}

void	mini_go(t_all *all)
{
	int	y;
	int	x;

	y = -1;
	while (++y < all->height)
	{
		x = -1;
		while (++x < all->width)
		{
			all->t_min = 1E99;
			init_dir(all, &all->dir, x, y);
			all->nearest[0] = '\0';
			all->closest.intens = 0;
			get_closest_t(all);
			if (all->t_min < 1E99)
			{
				light(all);
				my_mlx_pixel_put(&all->mlx, x, y, get_color(all->nearest, all,
						all->closest.intens));
			}
			if (all->t_min == 1E99)
				my_mlx_pixel_put(&all->mlx, x, y, 0);
		}
	}
}

int	main(int ac, char **av)
{
	t_all	all;

	if (checker(ac, &all, av[1]) != 1)
		return (0);
	camera_rotation(&all.camera);
	mini_go(&all);
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.window, all.mlx.img, 0, 0);
	mlx_hook(all.mlx.window, 33, 0, ft_exit, &all);
	mlx_hook(all.mlx.window, 2, 1L, key_press, &all);
	mlx_hook(all.mlx.window, 15, 1L << 16, minim_wind, &all);
	mlx_loop(all.mlx.mlx);
	return (0);
}
