/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:09:49 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 18:11:43 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_exit(t_all *all)
{
	printf("Goodbye\n");
	free(all->sp);
	free(all->pl);
	free(all->cy);
	mlx_destroy_image(all->mlx.mlx, all->mlx.img);
	mlx_destroy_window(all->mlx.mlx, all->mlx.window);
	mlx_destroy_display(all->mlx.mlx);
	free(all->mlx.mlx);
	exit(0);
	return (1);
}

int key_press(unsigned int key, t_all *all)
{
	if (key == 65307)
		ft_exit(all);
	return (0);
}

int minim_wind(t_all *all)
{
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.window, all->mlx.img, 0, 0);
	return (0);
}

int get_color(char *nearest, t_all *all, double intens)
{
	int i;

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

int ret_error_msg(char *msg, int ret)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (ret);
}

int checker(int ac, t_all *all, char *file)
{
	if (ac != 2)
		return (ret_error_msg("Please use the program with a .rt file.", 0));
	init_all(all);
	if (parse_rt(file, all) == -1)
		return (ret_error_msg("Parsing error.", 0));
	if (mlx_data_init(&all->mlx, all->width, all->height) != 1)
	{
		free(all->sp);
		free(all->pl);
		free(all->cy);
		return (ret_error_msg("mlx problem.", 0));
	}
	return (1);
}

void mini_go(t_all *all)
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
			if (all->t_min < 1E99) // intersection
			{
				light(all);
				my_mlx_pixel_put(&all->mlx, x, y, get_color(all->nearest, all,
						all->closest.intens));
			}
			if (all->t_min == 1E99) // no intersection ever
				my_mlx_pixel_put(&all->mlx, x, y, 0);
		}
	}
}

int main(int ac, char **av)
{
	t_all all;

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
