/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:29:43 by threiss           #+#    #+#             */
/*   Updated: 2021/08/26 12:38:33 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
**	function gets t_min of all objects
*/

void get_closest_t(t_all *all, double *t_min)
{
	int i;

	i = -1;
	while (++i < all->checkrt.cy)
	{
		all->t_tmp = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_cy(all, &all->cylinder[i]) == 1)
		{
			if (all->t_tmp < *t_min && all->t_tmp >= 0)
			{
				all->nearest[0] = 'c';
				all->nearest[1] = 'y';
				all->nearest[2] = i + 48;
				*t_min = all->t_tmp;
				all->P = all->closest.p_local;
				all->N = all->closest.n_local;
			}
		}
	}
	i = -1;
	while (++i < all->checkrt.sp)
	{
		all->t_tmp = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_sp(all, all->camera.cam, all->direction, all->sphere[i], &all->closest.p_local, &all->closest.n_local) == 1)
		{
			if (all->t_tmp < *t_min && all->t_tmp >= 0)
			{
				all->nearest[0] = 's';
				all->nearest[1] = 'p';
				all->nearest[2] = i + 48;
				*t_min = all->t_tmp;
				all->P = all->closest.p_local;
				all->N = all->closest.n_local;
			}
		}
	}
	i = -1;
	while (++i < all->checkrt.pl)
	{
		all->t_tmp = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_pl(all, all->camera.cam, all->direction, all->plane[i], &all->closest.p_local, &all->closest.n_local) == 1)
		{
			if (all->t_tmp < *t_min && all->t_tmp >= 0)
			{
				all->nearest[0] = 'p';
				all->nearest[1] = 'l';
				all->nearest[2] = i + 48;
				*t_min = all->t_tmp;
				all->P = all->closest.p_local;
				all->N = all->closest.n_local;
			}
		}
	}
}