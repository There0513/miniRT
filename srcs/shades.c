/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:12:16 by threiss           #+#    #+#             */
/*   Updated: 2021/09/07 15:12:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int shadow_sp(t_all *all, t_sphere sphere, t_vector P, t_vector dir)
{
	t_vector PC; // hitPoint - center

	PC = add_min_operation('-', P, sphere.center);
	double a = dot(dir, dir);
	double b = 2 * dot(dir, PC);
	double c = pow(sqrt(dot(PC, PC)), 2) - sphere.radius * sphere.radius;
	double delta = b * b - (4 * a * c);
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);
	if (t1 >= 0)
	{
		all->t_visib = t1;
		return (1);
	}
	else if (t2 >= 0)
	{
		all->t_visib = t2;
		return (1);
	}
	return (0);
}

// cy
int shad_cy(t_all *all, t_vector camera, double t, t_vector direction, t_cylinder cylinder)
{
	t_vector point = add_min_operation('+', camera, mult_operation('*', t, direction));
	double z = dot(add_min_operation('-', point, cylinder.vec), cylinder.forward);
	if (fabs(z) > cylinder.height / 2.0)
		return (-1);
	all->t_visib = t;
	return (1);
}

int shadow_cy(t_all *all, t_cylinder cylinder, t_vector P, t_vector dir)
{
	cylinder_rotation2(&cylinder); // neccesairy for shadow cy
	t_vector OV = add_min_operation('-', P, cylinder.vec); // Origin - Vec
	double a = pow(dot(dir, cylinder.right), 2) + pow(dot(dir, cylinder.up), 2);
	double b = 2 * (dot(dir, cylinder.right) * dot(OV, cylinder.right) + dot(dir, cylinder.up) * dot(OV, cylinder.up));
	double c = pow(dot(OV, cylinder.right), 2) + pow(dot(OV, cylinder.up), 2) - pow(cylinder.radius, 2);
	double delta = b * b - (4 * a * c);
	// printf("a = %f b = %f c = %f\n", a, b, c);
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);
	if (t1 > 0)
	{
		if (shad_cy(all, P, t1, dir, cylinder) == 1)
			return (1);
	}
	if (t2 > 0)
	{	
		if (shad_cy(all, P, t2, dir, cylinder) == 1)
			return (1);
		// t_vector point = add_min_operation('+', P, mult_operation('*', t2, dir));
		// double z = dot(add_min_operation('-', point, cylinder.vec), cylinder.forward);
		// if (fabs(z) > cylinder.height / 2.0)
		// 	return (-1);
		// all->t_visib = t2;
		// return (1);
	}
	return (0);
}

// pl
int shadow_pl(t_all *all, t_plane plane, t_vector P, t_vector dir)
{
	double tmp_t;
	double a = dot(plane.orient, add_min_operation('-', P, plane.vec));
	double b = dot(plane.orient, dir);
	// printf("a = %f\tb = %f\n", a, b);
	if (!b)
		return (-1);
	tmp_t = -a / b;
	if (tmp_t >= 0)
	{
		all->t_visib = tmp_t;
		return (1);
	}
	return (-1);
}
