/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:10:23 by threiss           #+#    #+#             */
/*   Updated: 2021/09/19 17:28:04 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
**	1920x1080 for correction
*/
void	init_all(t_all *all)
{
	all->width = 1920;
	all->height = 1080;
	all->p = create_vec(0, 0, 0);
	all->n = create_vec(0, 0, 0);
	all->checkrt.a = 0;
	all->checkrt.c = 0;
	all->checkrt.l = 0;
	all->checkrt.pl = 0;
	all->checkrt.sp = 0;
	all->checkrt.cy = 0;
	all->checkrt.add_pl = 0;
	all->checkrt.add_sp = 0;
	all->checkrt.add_cy = 0;
}

void	init_dir(t_all *all, t_vector *dir, int x, int y)
{
	t_vector	tmp;

	tmp.x = x - all->width / 2;
	tmp.y = (all->height / 2) - y;
	tmp.z = all->width / (2 * tan(all->camera.fov / 2));
	dir->x = tmp.x * all->camera.right.x + tmp.y * all->camera.up.x
		+ tmp.z * all->camera.forward.x;
	dir->y = tmp.x * all->camera.right.y + tmp.y * all->camera.up.y
		+ tmp.z * all->camera.forward.y;
	dir->z = tmp.x * all->camera.right.z + tmp.y * all->camera.up.z
		+ tmp.z * all->camera.forward.z;
	normalize(dir);
}

void	camera_rotation(t_camera *camera)
{
	t_vector	tmp;

	tmp = create_vec(0, 1, 0);
	camera->forward = get_normalized(camera->orient);
	if (camera->forward.y == 1 || camera->forward.y == -1)
		camera->right = create_vec(1, 0, 0);
	else
		camera->right = cross_prod(get_normalized(tmp), camera->forward);
	camera->up = cross_prod(camera->forward, camera->right);
	normalize(&camera->forward);
	normalize(&camera->right);
	normalize(&camera->up);
}

void	cylinder_rotation(t_cylinder *cylinder)
{
	t_vector	tmp;

	tmp = create_vec(0, -1, 0);
	cylinder->forward = get_normalized(cylinder->orient);
	if (cylinder->forward.y == 1 || cylinder->forward.y == -1)
		cylinder->right = get_normalized(create_vec(1, 0, 0));
	else
		cylinder->right = cross_prod(tmp, cylinder->forward);
	cylinder->up = cross_prod(cylinder->forward, cylinder->right);
	normalize(&cylinder->forward);
	normalize(&cylinder->right);
	normalize(&cylinder->up);
}
