/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:29:43 by threiss           #+#    #+#             */
/*   Updated: 2021/08/02 18:43:34 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_closest_t(t_all *all, t_vector *P, t_vector *N, double *t_min)
{
	int			i;
	double		t;

	i = -1;
	while (++i < all->checkrt.sp)
	{
		t = 0;
		all->closest.p_local = create_vec(0, 0, 0);
		all->closest.n_local = create_vec(0, 0, 0);
		if (intersection_sp(all->camera.cam, all->direction, all->sphere[i], &all->closest.p_local, &all->closest.n_local, &t) == 1)
		{
			all->nearest[0] = 's';
			all->nearest[1] = 'p';
			all->nearest[2] = i + 48;		// nearest sphere/point [i]
			// printf("nearest = %s\n", all->nearest);
			printf("t in get_closest_t = %f\n", t);
			if (t < *t_min)
			{
				*t_min = t;
				*P = all->closest.p_local;
				*N = all->closest.n_local;
			}
		}
	}
	//	while (planes)
	//	while (cylinders)

}
