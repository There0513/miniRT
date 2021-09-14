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

void get_closest_t(t_all *all, t_vector *P, t_vector *N, double *t_min)
{
	int i;
	double t;

	i = -1;
	while (++i < all->checkrt.sp)
	{
		t = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_sp(all->camera.cam, all->direction, all->sphere[i], &all->closest.p_local, &all->closest.n_local, &t) == 1)
		{
			if (t < *t_min)
			{
				all->nearest[0] = 's';
				all->nearest[1] = 'p';
				all->nearest[2] = i + 48;
				*t_min = t;
				*P = all->closest.p_local;
				*N = all->closest.n_local;
			}
		}
	}
	i = -1;
	while (++i < all->checkrt.pl)
	{
		t = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_pl(all->camera.cam, all->direction, all->plane[i], &all->closest.p_local, &all->closest.n_local, &t) == 1)
		{
			if (t < *t_min && t >= 0)
			{
				all->nearest[0] = 'p';
				all->nearest[1] = 'l';
				all->nearest[2] = i + 48;
				*t_min = t;
				*P = all->closest.p_local;
				*N = all->closest.n_local;
			}
		}
	}
	i = -1;
	while (++i < all->checkrt.cy)
	{
		t = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_cy(all, all->camera.cam, all->direction, &all->cylinder[i], &all->closest.p_local, &all->closest.n_local, &t) == 1)
		{
			if (t < *t_min && t >= 0)
			{
				all->nearest[0] = 'c';
				all->nearest[1] = 'y';
				all->nearest[2] = i + 48;
				*t_min = t;
				*P = all->closest.p_local;
				*N = all->closest.n_local;
			}
		}
	}
} // 		--->> function gets t_min of all objects
