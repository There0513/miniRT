/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:48:06 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 22:48:44 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	visib_sp(t_all all, t_vector P, t_visib vis, t_sphere sp)
{
	if (shadow_sp(&all, sp, P, vis.dir) == 1)
	{
		if (all.nearest[0] == 'c')
			return (1);
		vis.p2 = calc_op('+', P, mult_op('*', all.t_visib, vis.dir));
		vis.light_p = calc_op('-', all.light.point_l, P);
		vis.p2_p = calc_op('-', vis.p2, P);
		vis.a = sqrt(get_norm(&vis.light_p));
		vis.b = sqrt(get_norm(&vis.p2_p));
		if (vis.b < vis.a)
			return (0);
	}
	return (2);
}

int	visib_cy(t_all all, t_visib vis, t_cylinder *cy)
{
	if (shadow_cy(&all, cy, vis.dir) == 1)
	{
		vis.p2 = calc_op('+', all.p, mult_op('*', all.t_visib, vis.dir));
		vis.light_p = calc_op('-', all.light.point_l, all.p);
		vis.p2_p = calc_op('-', vis.p2, all.p);
		vis.a = sqrt(get_norm(&vis.light_p));
		vis.b = sqrt(get_norm(&vis.p2_p));
		if (vis.b < vis.a)
			return (0);
	}
	return (2);
}

int	visib_pl(t_all all, t_vector P, t_visib vis, t_plane pl)
{
	if (shadow_pl(&all, pl, P, vis.dir) == 1)
	{
		if (all.nearest[0] == 'c')
			return (1);
		vis.p2 = calc_op('+', P, mult_op('*', all.t_visib, vis.dir));
		vis.light_p = calc_op('-', all.light.point_l, P);
		vis.p2_p = calc_op('-', vis.p2, P);
		vis.a = sqrt(get_norm(&vis.light_p));
		vis.b = sqrt(get_norm(&vis.p2_p));
		if (vis.b < vis.a)
			return (0);
	}
	return (2);
}

/*
 **  visibility() returns 0 or 1
 */

int	visibility(t_all *all)
{
	t_visib	vis;

	vis.dir = get_normalized(calc_op('-', all->light.point_l, all->p));
	vis.i = -1;
	while (++vis.i < all->checkrt.sp)
	{
		vis.ret = visib_sp(*all, all->p, vis, all->sp[vis.i]);
		if (vis.ret != 2)
			return (vis.ret);
	}
	vis.i = -1;
	while (++vis.i < all->checkrt.cy)
	{
		vis.ret = visib_cy(*all, vis, &all->cy[vis.i]);
		if (vis.ret != 2)
			return (vis.ret);
	}
	vis.i = -1;
	while (++vis.i < all->checkrt.pl)
	{
		vis.ret = visib_pl(*all, all->p, vis, all->pl[vis.i]);
		if (vis.ret != 2)
			return (vis.ret);
	}
	return (1);
}

void	light(t_all *all)
{
	double		is_visible;
	t_vector	ptolight;
	t_vector	next;

	ptolight = calc_op('-', all->light.point_l, all->p);
	normalize(&ptolight);
	all->p = calc_op('+', all->p, mult_op('*', 0.0001, all->n));
	is_visible = visibility(all);
	next = calc_op('-', all->light.point_l, all->p);
	all->closest.intens = all->light.bright_l * dot(all->n, ptolight)
		* is_visible / pow(sqrt(get_norm(&next)) / 100, 2);
	if (all->closest.intens < 0.00)
		all->closest.intens = 0;
}
