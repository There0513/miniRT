/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:12:16 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 19:58:04 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	shadow_sp(t_all *all, t_sphere sphere, t_vector P, t_vector dir)
{
	t_vector	pc;
	t_inters	tab;

	pc = calc_op('-', P, sphere.center);
	tab.a = dot(dir, dir);
	tab.b = 2 * dot(dir, pc);
	tab.c = pow(sqrt(dot(pc, pc)), 2) - sphere.radius * sphere.radius;
	tab.delta = tab.b * tab.b - (4 * tab.a * tab.c);
	if (tab.delta < 0)
		return (-1);
	tab.t1 = (-tab.b - sqrt(tab.delta)) / (2.0 * tab.a);
	tab.t2 = (-tab.b + sqrt(tab.delta)) / (2.0 * tab.a);
	if (tab.t1 > 0)
	{
		all->t_visib = tab.t1;
		return (1);
	}
	else if (tab.t2 > 0)
	{
		all->t_visib = tab.t2;
		return (1);
	}
	return (0);
}

int	shad_cy(t_all *all, double t, t_vector direction, t_cylinder cylinder)
{
	t_vector	point;
	double		z;

	point = calc_op('+', all->p, mult_op('*', t, direction));
	z = dot(calc_op('-', point, cylinder.vec), cylinder.forward);
	if (fabs(z) > cylinder.height / 2.0)
		return (-1);
	all->t_visib = t;
	return (1);
}

int	shadow_cy(t_all *all, t_cylinder *cylinder, t_vector dir)
{
	t_inters	tab;
	t_vector	ov;

	ov = calc_op('-', all->p, cylinder->vec);
	tab.a = pow(dot(dir, cylinder->right), 2) + pow(dot(dir, cylinder->up), 2);
	tab.b = 2 * (dot(dir, cylinder->right) * dot(ov, cylinder->right)
			+ dot(dir, cylinder->up) * dot(ov, cylinder->up));
	tab.c = pow(dot(ov, cylinder->right), 2) + pow(dot(ov, cylinder->up), 2)
		- pow(cylinder->radius, 2);
	tab.delta = tab.b * tab.b - (4 * tab.a * tab.c);
	if (tab.delta < 0)
		return (-1);
	tab.t1 = (-tab.b - sqrt(tab.delta)) / (2.0 * tab.a);
	tab.t2 = (-tab.b + sqrt(tab.delta)) / (2.0 * tab.a);
	if (tab.t1 > 0)
	{
		if (shad_cy(all, tab.t1, dir, *cylinder) == 1)
			return (1);
	}
	if (tab.t2 > 0)
	{	
		if (shad_cy(all, tab.t2, dir, *cylinder) == 1)
			return (1);
	}
	return (0);
}

int	shadow_pl(t_all *all, t_plane plane, t_vector P, t_vector dir)
{
	double	tmp_t;
	double	a;
	double	b;

	a = dot(plane.orient, calc_op('-', P, plane.vec));
	b = dot(plane.orient, dir);
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
