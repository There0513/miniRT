/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:11:12 by threiss           #+#    #+#             */
/*   Updated: 2021/08/07 17:05:07 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// intersections.c
int	intersection_sp(t_vector camera, t_vector direction, t_sphere sphere, t_vector *P, t_vector *N, double *t)
{// camera = d.origin
	// resout a * t ^ 2 + b * t + c = 0
	t_vector	OC; // ray.origin - sphere.center
	OC = add_min_operation('-', camera, sphere.center);
	double	a = dot(direction, direction);
	double	b = 2 * dot(direction, OC);
	double	c = pow(sqrt(dot(OC, OC)), 2) - sphere.radius * sphere.radius; // pow(diameter/2)
	// = dot(OC, OC) - ray * ray...
	double	delta = b * b - (4 * a * c);
	// if (delta >= 0)
	// 	printf("a %f b %f c%f\ndelta %f\n", a, b, c, delta);
	if (delta < 0)
		return (-1);
	double	t1 = (-b - sqrt(delta)) / (2.0 * a);
	double	t2 = (-b + sqrt(delta)) / (2.0 * a);
//	printf("\t\tt1 = %f\tt2 = %f\n", t1, t2);
	if (t2 < 0)
		return (-1); // pas d'intersection
	/* t < 0			behind the camera
	   0 <= t <= 1		between camera & projection plane
	   t > 1 			in front of projection plane */
	// intersection
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;
	//-> manage light:
	*P = add_min_operation('+', camera ,mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(add_min_operation('-', *P, sphere.center));
	//N = normalize(add_min_operation('-', P, sphere)); // normalize(P - sphere)
	return (1);
}

int	intersection_pl(t_vector camera, t_vector direction, t_plane plane, t_vector *P, t_vector *N, double *t)
{
	double	a = dot(plane.orient, add_min_operation('-', camera, plane.vec));
	double	b = dot(plane.orient, direction);
	printf("a = %f\tb = %f\n", a, b);
	if (!b)
		return (-1);
	*t = -a / b;
	*P = add_min_operation('+', camera ,mult_operation('*', *t, direction)); // camera + t * direction		P = intersection point = ray origin + t * ray direction
	*N = get_normalized(plane.orient);
	return (1);
}
