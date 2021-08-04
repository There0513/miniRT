/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:10:23 by threiss           #+#    #+#             */
/*   Updated: 2021/08/04 16:32:59 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_all(t_all *all)	// to avoid error message not initialized
{
	all->checkrt.A = 0;
	all->checkrt.C = 0;
	all->checkrt.L = 0;
	all->checkrt.pl = 0;
	all->checkrt.sp = 0;
	all->checkrt.cy = 0;
}

void	init_others_tmp(t_vector *P, t_vector *N)
{
	P->x = 0;
	P->y = 0;
	P->z = 0;

	N->x = 0;
	N->y = 0;
	N->z = 0;
}

t_list	*ft_create_elem(t_sphere *sphere)
{
	t_list	*scenes;

	if (!(scenes = malloc(sizeof(t_list))))
		return (0);
		scenes->sp = *sphere;
		scenes->next = 0;
		return (scenes);
}

void	init_dir(t_vector *direction, int x, int y, double fov, t_camera camera)
{
	t_vector	tmp;

	tmp.x = x - WIDTH_DEF / 2;
	tmp.y = (HEIGHT_DEF / 2) - y;
	tmp.z = WIDTH_DEF / (2 * tan(fov / 2));
	direction->x = tmp.x * camera.right.x + tmp.y * camera.up.x + tmp.z * camera.forward.x;
	direction->y = tmp.x * camera.right.y + tmp.y * camera.up.y + tmp.z * camera.forward.y;
	direction->x = tmp.x * camera.right.x + tmp.y * camera.up.x + tmp.z * camera.forward.x;
	direction->z = tmp.x * camera.right.z + tmp.y * camera.up.z + tmp.z * camera.forward.z;
	normalize(direction);
}

t_vector	cross_prod(t_vector a, t_vector b)
{
	t_vector cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
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
	// normalize forward, right + up?!?!?!
	normalize(&camera->forward);
	normalize(&camera->right);
	normalize(&camera->up);
//printf("up %f %f %f\n forward %f %f %f\n right %f %f %f\n", camera->up.x, camera->up.y,camera->up.z, camera->forward.x, camera->forward.y, camera->forward.z, camera->right.x, camera->right.y, camera->right.z);
}
