/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:09:49 by threiss           #+#    #+#             */
/*   Updated: 2021/08/26 17:58:50 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_exit(t_all *all)
{
	printf("exit\n");
	// free data/structs
	free(all->sphere);
	free(all->plane);
	free(all->cylinder);

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

int get_color(char *nearest, t_all all)
{
	int i;

	// if (all.closest.intensity <= 0.0)
	// 	all.closest.intensity = 0.08;
	i = nearest[2] - 48;
	if (nearest[0] == 's' && nearest[1] == 'p')
		return (rgb_to_int(all.sphere[i].rgb.x * all.closest.intensity + all.sphere[i].rgb.x * 0.3, all.sphere[i].rgb.y * all.closest.intensity + all.sphere[i].rgb.y * 0.3,
						   all.sphere[i].rgb.z * all.closest.intensity + all.sphere[i].rgb.z * 0.3, all));
	if (nearest[0] == 'p' && nearest[1] == 'l')
		return (rgb_to_int(all.plane[i].rgb.x * all.closest.intensity + all.plane[i].rgb.x * 0.3, all.plane[i].rgb.y * all.closest.intensity + all.plane[i].rgb.y * 0.3,
						   all.plane[i].rgb.z * all.closest.intensity + all.plane[i].rgb.z * 0.3, all));
	if (nearest[0] == 'c' && nearest[1] == 'y')
	{
		// printf("br = %f\n", all.cylinder->br);
		return (rgb_to_int(all.cylinder[i].rgb.x * all.closest.intensity + all.cylinder[i].rgb.x * 0.3, all.cylinder[i].rgb.y * all.closest.intensity + all.cylinder[i].rgb.y * 0.3,
						   all.cylinder[i].rgb.z * all.closest.intensity + all.cylinder[i].rgb.z * 0.3, all));
	}
	return (16777215);
}

int main(int ac, char **av)
{
	t_all all;
	t_vector P, N;

	if (ac != 2)
	{
		printf("Please use the program with a valid .rt file -> ./minirt scene.rt\n");
		return (0);
	}
	init_all(&all); // all->checkrt.xy
	P = create_vec(0, 0, 0);
	N = create_vec(0, 0, 0);
	if (parse_rt(av[1], &all) == -1)
		return (0);
	// if width/height given -> change WIDTH_DEF / HEIGHT_DEF
	mlx_data_init(&all.mlx, WIDTH_DEF, HEIGHT_DEF);
	camera_rotation(&all.camera);
	for (int y = 0; y < HEIGHT_DEF; y++)
	{
	// if (all.light.point_l.y > 0)
		// all.cylinder->br = 1;
	// if (all.light.point_l.y < 0)
		// all.cylinder->br = 0;
		for (int x = 0; x < WIDTH_DEF; x++)
		{
			all.t_min = 1E99;
			init_dir(&all.direction, x, y, all.camera.fov, all.camera);
			all.nearest[0] = '\0';
			// all.closest.n_local = create_vec(0, 0, 0);
			// all.closest.p_local = create_vec(0, 0, 0);
			// all.closest.intensity = 0;
			get_closest_t(&all, &P, &N, &all.t_min);
			if (all.t_min < 1E99) // intersection
			{
				light(&all, P, N);
				my_mlx_pixel_put(&all.mlx, x, y, get_color(all.nearest, all));
			}
			if (all.t_min == 1E99) // no intersection ever
				my_mlx_pixel_put(&all.mlx, x, y, 0);
			// all.closest.intensity = 0;
		}
	}
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.window, all.mlx.img, 0, 0);
	mlx_hook(all.mlx.window, 33, 0, ft_exit, &all);
	mlx_hook(all.mlx.window, 2, 1L, key_press, &all);
	// mlx_hook(all.mlx.window, 3, 1L << 1, key_release, &all);
	mlx_loop(all.mlx.mlx);
	return (0);
}
