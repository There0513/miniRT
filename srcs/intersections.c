/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:11:12 by threiss           #+#    #+#             */
/*   Updated: 2021/08/11 13:31:33 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
**	intersection_sp() solve a * t ^ 2 + b * t + c = 0
**
**	t2 < 0 -> no intersection
**	t < 0			behind the camera
**	0 <= t <= 1		between camera & projection plane
**	t > 1 			in front of projection plane
**
**	P = intersection point = ray origin + t * ray direction
*/

int intersection_sp(t_all *all, t_sphere sphere)
{
	t_vector OC;
	t_inters tab;

	OC = calc_op('-', all->camera.cam, sphere.center);
	tab.a = dot(all->dir, all->dir);
	tab.b = 2 * dot(all->dir, OC);
	tab.c = pow(sqrt(dot(OC, OC)), 2) - sphere.radius * sphere.radius;
	tab.delta = tab.b * tab.b - (4 * tab.a * tab.c);
	if (tab.delta < 0)
		return (-1);
	tab.t1 = (-tab.b - sqrt(tab.delta)) / (2.0 * tab.a);
	tab.t2 = (-tab.b + sqrt(tab.delta)) / (2.0 * tab.a);
	if (tab.t2 < 0)
		return (-1);
	if (tab.t1 >= 0)
		all->t_tmp = tab.t1;
	else if (tab.t2 >= 0)
		all->t_tmp = tab.t2;
	all->closest.p_local = calc_op('+', all->camera.cam, mult_op('*', all->t_tmp, all->dir));
	all->closest.n_local = get_normalized(calc_op('-', all->closest.p_local, sphere.center));
	if (dot(all->dir, all->closest.n_local) > 0)
		all->closest.n_local = get_normalized(mult_op('*', -1, all->closest.n_local));
	return (1);
}

int intersection_pl(t_all *all, t_plane plane)
{
	t_inters tab;

	tab.a = dot(plane.orient, calc_op('-', all->camera.cam, plane.vec));
	tab.b = dot(plane.orient, all->dir);
	if (!tab.b)
		return (-1);
	all->t_tmp = -tab.a / tab.b;
	if (all->t_tmp < 0)
		return (-1);
	all->closest.p_local = calc_op('+', all->camera.cam, mult_op('*', all->t_tmp, all->dir));
	all->closest.n_local = get_normalized(plane.orient);
	if (dot(all->dir, all->closest.n_local) > 0)
		all->closest.n_local = mult_op('*', -1, all->closest.n_local);
	return (1);
}

int inter_cy(t_all *all, double t12, t_cylinder *cylinder)
{
	t_vector point;
	t_vector tmp;
	double z;

	point = calc_op('+', all->camera.cam, mult_op('*', t12, all->dir));
	z = dot(calc_op('-', point, cylinder->vec), cylinder->forward);
	if (fabs(z) > cylinder->height / 2.0)
		return (-1);
	all->t_tmp = t12;
	all->closest.p_local = calc_op('+', all->camera.cam, mult_op('*', all->t_tmp, all->dir));
	tmp = get_normalized(calc_op('-', all->closest.p_local, cylinder->vec));
	all->closest.n_local = get_normalized(calc_op('-', tmp,
												  mult_op('*', dot(get_normalized(cylinder->orient), tmp), get_normalized(cylinder->orient))));
	if (dot(all->dir, all->closest.n_local) > 0)
		all->closest.n_local = get_normalized(mult_op('*', -1, all->closest.n_local));
	return (1);
}

/*
**	if (t2 < 0)
**	return (-1); // pas d'intersection
**	if (t1 > 0)
**	*t = t1;
**	else
**	*t = t2;
*/

int intersection_cy(t_all *all, t_cylinder *cy)
{
	t_vector OV;
	t_inters tab;

	cylinder_rotation(cy);
	OV = calc_op('-', all->camera.cam, cy->vec);
	tab.a = pow(dot(all->dir, cy->right), 2) + pow(dot(all->dir, cy->up), 2);
	tab.b = 2 * (dot(all->dir, cy->right) * dot(OV, cy->right) + dot(all->dir, cy->up) * dot(OV, cy->up));
	tab.c = pow(dot(OV, cy->right), 2) + pow(dot(OV, cy->up), 2) - pow(cy->radius, 2);
	tab.delta = tab.b * tab.b - 4 * tab.a * tab.c;
	if (tab.delta < 0)
		return (-1);
	tab.t1 = (-tab.b - sqrt(tab.delta)) / (2.0 * tab.a);
	tab.t2 = (-tab.b + sqrt(tab.delta)) / (2.0 * tab.a);
	if (tab.t1 >= 0)
		if (inter_cy(all, tab.t1, cy) == 1)
			return (1);
	if (tab.t2 >= 0)
		if (inter_cy(all, tab.t2, cy) == 1)
			return (1);
	return (0);
}