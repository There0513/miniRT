/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:29:43 by threiss           #+#    #+#             */
/*   Updated: 2021/09/17 22:08:06 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
**	function gets t_min of all objects
*/

void	closest_cy(t_all *all, t_cylinder *cylinder, int i)
{
	all->t_tmp = 0;
	all->closest.p_local = create_vec(0, 0, 0);
	all->closest.n_local = create_vec(0, 0, 0);
	if (intersection_cy(all, cylinder) == 1)
	{
		if (all->t_tmp < all->t_min && all->t_tmp >= 0)
		{
			all->nearest[0] = 'c';
			all->nearest[1] = 'y';
			all->nearest[2] = i + 48;
			all->t_min = all->t_tmp;
			all->p = all->closest.p_local;
			all->n = all->closest.n_local;
		}
	}
}

void	closest_sp(t_all *all, t_sphere sphere, int i)
{
	all->t_tmp = 0;
	all->closest.p_local = create_vec(0, 0, 0);
	all->closest.n_local = create_vec(0, 0, 0);
	if (intersection_sp(all, sphere) == 1)
	{
		if (all->t_tmp < all->t_min && all->t_tmp >= 0)
		{
			all->nearest[0] = 's';
			all->nearest[1] = 'p';
			all->nearest[2] = i + 48;
			all->t_min = all->t_tmp;
			all->p = all->closest.p_local;
			all->n = all->closest.n_local;
		}
	}
}

void	closest_pl(t_all *all, t_plane plane, int i)
{
	all->t_tmp = 0;
	all->closest.p_local = create_vec(0, 0, 0);
	all->closest.n_local = create_vec(0, 0, 0);
	if (intersection_pl(all, plane) == 1)
	{
		if (all->t_tmp < all->t_min && all->t_tmp >= 0)
		{
			all->nearest[0] = 'p';
			all->nearest[1] = 'l';
			all->nearest[2] = i + 48;
			all->t_min = all->t_tmp;
			all->p = all->closest.p_local;
			all->n = all->closest.n_local;
		}
	}
}

void	get_closest_t(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->checkrt.cy)
		closest_cy(all, &all->cy[i], i);
	i = -1;
	while (++i < all->checkrt.sp)
		closest_sp(all, all->sp[i], i);
	i = -1;
	while (++i < all->checkrt.pl)
		closest_pl(all, all->pl[i], i);
}
