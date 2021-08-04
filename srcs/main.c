/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:09:49 by threiss           #+#    #+#             */
/*   Updated: 2021/08/04 18:02:51 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_all		all;
	t_vector	P, N, tmp;

	if (ac != 2)
	{
		printf("Please use the program with a valid .rt file -> ./minirt scene.rt\n");
		return (0);
	}
	init_all(&all);
	init_others_tmp(&P, &N);
	if (parse_rt(av[1], &all) == -1)
		return (0);
	// if width/height given -> change WIDTH_DEF / HEIGHT_DEF
	mlx_data_init(&all.mlx, WIDTH_DEF, HEIGHT_DEF);
	camera_rotation(&all.camera);
	for (int y = 0; y < HEIGHT_DEF; y++)
	{
		for (int x = 0; x < WIDTH_DEF; x++)
		{
			all.t_min = 1E99;
			init_dir(&all.direction, x, y, all.camera.fov, all.camera);
			get_closest_t(&all, &P, &N, &all.t_min);
			if (all.t_min < 1E99)	// intersection
			{
				tmp = add_min_operation('-', all.light.point_l, P);
//				normalize(&tmp);
//				double dotdot = dot(tmp, N);
//				all.light.bright_l += all.light.bright_l * dotdot / (sqrt(getNorm2(&N)) * sqrt(getNorm2(&tmp)));
				//intensite_pixel = l_bright * dot(normalize(light - P), N) / getNorm2(light - P);
//				if (dotdot < 0)	// -> in the 'shadow'/darkside		is visible?! function
				my_mlx_pixel_put(&all.mlx, x, HEIGHT_DEF - y - 1, rgb_to_int(255, 117, 255));
				//my_mlx_pixel_put(&all.mlx, x, HEIGHT_DEF - y - 1, rgb_to_int((int)this_sphere.rgb.x * all.light.bright_l, (int)this_sphere.rgb.y * all.light.bright_l, (int)this_sphere.rgb.z * all.light.bright_l));
			}
			if (all.t_min == 1E99)	// no intersection ever
			{printf("here");
				my_mlx_pixel_put(&all.mlx, x, HEIGHT_DEF - y - 1,
				rgb_to_int((int)all.light.ambient_rgb.x * all.light.ambient_l, (int)all.light.ambient_rgb.y * all.light.ambient_l ,(int)all.light.ambient_rgb.z * all.light.ambient_l));
			}
		}
	}
	printf("end\n");
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.window, all.mlx.img, 0, 0);
	mlx_loop(all.mlx.mlx);
	return (0);
}
