/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:09:49 by threiss           #+#    #+#             */
/*   Updated: 2021/08/02 18:48:28 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_all		all;
	t_vector	P, N, tmp;
	double		t_min = 1E99;

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
//	camera_rotation(&camera);
	for (int y = 0; y < HEIGHT_DEF; y++)
	{
		for (int x = 0; x < WIDTH_DEF; x++)
		{
			init_dir(&all.direction, x, y, all.camera.fov, all.camera);
			printf("\ntmin = %f\n", t_min);
			get_closest_t(&all, &P, &N, &t_min);
			if (t_min < 1E99)	// intersection
			{
				printf("yes\n");
				tmp = add_min_operation('-', all.light.point_l, P);
				normalize(&tmp);
				double dotdot = dot(tmp, N);
				all.light.bright_l += all.light.bright_l * dotdot / (sqrt(getNorm2(&N)) * sqrt(getNorm2(&tmp)));
				//intensite_pixel = l_bright * dot(normalize(light - P), N) / getNorm2(light - P);
				//if (dotdot < 0)	// -> in the 'shadow'/darkside		is visible?! function
		//		my_mlx_pixel_put(&all.mlx, x, HEIGHT_DEF - y - 1, rgb_to_int((int)this_sphere.rgb.x * all.light.bright_l, (int)this_sphere.rgb.y * all.light.bright_l, (int)this_sphere.rgb.z * all.light.bright_l));
			}
//			if (all.closest.t_min == 1E99)	// no intersection ever
//				my_mlx_pixel_put(&all.mlx, x, HEIGHT_DEF - y - 1, rgb_to_int((int)light.ambient_rgb.x * light.ambient_l, (int)light.ambient_rgb.y * light.ambient_l ,(int)light.ambient_rgb.z * light.ambient_l));
		}
	}
	printf("end\n");
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.window, all.mlx.img, 0, 0);
	mlx_loop(all.mlx.mlx);
	return (0);
}
