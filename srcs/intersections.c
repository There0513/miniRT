/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:11:12 by threiss           #+#    #+#             */
/*   Updated: 2021/08/11 13:31:33 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int intersection_sp(t_all *all, t_vector camera, t_vector direction, t_sphere sphere, t_vector *P, t_vector *N)
{ // camera = d.origin
	// resout a * t ^ 2 + b * t + c = 0
	t_vector OC; // ray.origin - sphere.center
	OC = add_min_operation('-', camera, sphere.center);
	double a = dot(direction, direction);
	double b = 2 * dot(direction, OC);
	double c = pow(sqrt(dot(OC, OC)), 2) - sphere.radius * sphere.radius; // pow(diameter/2)
	// = dot(OC, OC) - ray * ray...
	double delta = b * b - (4 * a * c);
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);

	if (t2 < 0)
		return (-1); // pas d'intersection
	/* t < 0			behind the camera
	   0 <= t <= 1		between camera & projection plane
	   t > 1 			in front of projection plane */
	// intersection:
	if (t1 >= 0)
		all->t_tmp = t1;
	else if (t2 >= 0)
		all->t_tmp = t2;
	//-> manage light: add is_visible to each manage-light ?!
	*P = add_min_operation('+', camera, mult_operation('*', all->t_tmp, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(add_min_operation('-', *P, sphere.center));
	if (dot(direction, *N) > 0)
		*N = get_normalized(mult_operation('*', -1, *N));
	return (1);
}

int intersection_pl(t_all *all, t_vector camera, t_vector direction, t_plane plane, t_vector *P, t_vector *N)
{
	double a = dot(plane.orient, add_min_operation('-', camera, plane.vec));
	double b = dot(plane.orient, direction);

	if (!b)
		return (-1);
	all->t_tmp = -a / b;
	if (all->t_tmp < 0)
		return (-1);
	*P = add_min_operation('+', camera, mult_operation('*', all->t_tmp, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(plane.orient);
	if (dot(direction, *N) > 0)
		*N = mult_operation('*', -1, *N);
	return (1);
}

int inter_cy(t_all *all, double t12, t_cylinder *cylinder)
{
	t_vector point = add_min_operation('+', all->camera.cam, mult_operation('*', t12, all->direction));
	double z = dot(add_min_operation('-', point, cylinder->vec), cylinder->forward);
	if (fabs(z) > cylinder->height / 2.0)
		return (-1);
	all->t_tmp = t12;
	all->closest.p_local = add_min_operation('+', all->camera.cam, mult_operation('*', all->t_tmp, all->direction)); // camera + t * di rection		P = intersection point = ray origin + t * ray di rection
	t_vector tmp = get_normalized(add_min_operation('-', all->closest.p_local, cylinder->vec));
	all->closest.n_local = get_normalized(add_min_operation('-', tmp,
															mult_operation('*', dot(get_normalized(cylinder->orient), tmp), get_normalized(cylinder->orient))));

	if (dot(all->direction, all->closest.n_local) > 0)
		all->closest.n_local = get_normalized(mult_operation('*', -1, all->closest.n_local));
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

int intersection_cy(t_all *all, t_cylinder *cylinder)
{
	cylinder_rotation(cylinder);
	t_vector OV = add_min_operation('-', all->camera.cam, cylinder->vec); // Origin - Vec
	double a = pow(dot(all->direction, cylinder->right), 2) + pow(dot(all->direction, cylinder->up), 2);
	double b = 2 * (dot(all->direction, cylinder->right) * dot(OV, cylinder->right) + dot(all->direction, cylinder->up) * dot(OV, cylinder->up));
	double c = pow(dot(OV, cylinder->right), 2) + pow(dot(OV, cylinder->up), 2) - pow(cylinder->radius, 2); // radius / 2 ?!?!?
	double delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);
	if (t1 >= 0)
		if (inter_cy(all, t1, cylinder) == 1)
			return (1);
	if (t2 >= 0)
		if (inter_cy(all, t2, cylinder) == 1)
			return (1);
	return (0);
}