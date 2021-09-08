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

int intersection_sp(t_vector camera, t_vector direction, t_sphere sphere, t_vector *P, t_vector *N, double *t)
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
		*t = t1;
	else if (t2 >= 0)
		*t = t2;
	//-> manage light: add is_visible to each manage-light ?!
	*P = add_min_operation('+', camera, mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(add_min_operation('-', *P, sphere.center));
	if (dot(direction, *N) > 0)
		// printf("\tdot > 0 in sphere -> add line *N?!?\n");
		*N = get_normalized(mult_operation('*', -1, *N));
	return (1);
}

int intersection_pl(t_vector camera, t_vector direction, t_plane plane, t_vector *P, t_vector *N, double *t)
{
	double a = dot(plane.orient, add_min_operation('-', camera, plane.vec));
	double b = dot(plane.orient, direction);

	if (!b)
		return (-1);
	*t = -a / b;
	if (*t < 0)
		return (-1);
	*P = add_min_operation('+', camera, mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(plane.orient);
	if (dot(direction, *N) > 0)
		*N = mult_operation('*', -1, *N);
	return (1);
}

int intersection_cy(t_vector camera, t_vector direction, t_cylinder cylinder, t_vector *P, t_vector *N, double *t)
{
	cylinder_rotation(&cylinder);
	t_vector OV = add_min_operation('-', camera, cylinder.vec); // Origin - Vec
	double a = pow(dot(direction, cylinder.right), 2) + pow(dot(direction, cylinder.up), 2);
	double b = 2 * (dot(direction, cylinder.right) * dot(OV, cylinder.right) + dot(direction, cylinder.up) * dot(OV, cylinder.up));
	double c = pow(dot(OV, cylinder.right), 2) + pow(dot(OV, cylinder.up), 2) - pow(cylinder.radius, 2);
	double delta = b * b - (4 * a * c);
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);
	/*	if (t2 < 0)
		return (-1); // pas d'intersection
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;*/
	if (t1 >= 0)
	{
		t_vector point = add_min_operation('+', camera, mult_operation('*', t1, direction));
		double z = dot(add_min_operation('-', point, cylinder.vec), cylinder.forward);
		if (fabs(z) > cylinder.height / 2.0)
			return (-1);
		*t = t1;
		*P = add_min_operation('+', camera, mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
		t_vector tmp = get_normalized(add_min_operation('-', *P, cylinder.vec));
		*N = get_normalized(add_min_operation('-', tmp,
											  mult_operation('*', dot(get_normalized(cylinder.orient), tmp), get_normalized(cylinder.orient))));
		if (dot(direction, *N) > 0)
			*N = get_normalized(mult_operation('*', -1, *N));
		return (1);
	}
	if (t2 >= 0)
	{
		t_vector point = add_min_operation('+', camera, mult_operation('*', t2, direction));
		double z = dot(add_min_operation('-', point, cylinder.vec), cylinder.forward);
		if (fabs(z) > cylinder.height / 2.0)
			return (-1);
		*t = t2;
		*P = add_min_operation('+', camera, mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
		t_vector tmp = get_normalized(add_min_operation('-', *P, cylinder.vec));
		*N = get_normalized(add_min_operation('-', tmp,
											  mult_operation('*', dot(get_normalized(cylinder.orient), tmp), get_normalized(cylinder.orient))));
		if (dot(direction, *N) > 0)
			*N = get_normalized(mult_operation('*', -1, *N));
		return (1);
	}
	return (0);
}