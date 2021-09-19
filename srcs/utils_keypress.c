/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:26:47 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 19:26:48 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	ft_exit(t_all *all)
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

int	key_press(unsigned int key, t_all *all)
{
	if (key == 65307)
		ft_exit(all);
	return (0);
}

int	minim_wind(t_all *all)
{
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.window, all->mlx.img, 0, 0);
	return (0);
}
