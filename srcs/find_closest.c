/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:29:43 by threiss           #+#    #+#             */
/*   Updated: 2021/08/02 16:34:01 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_closest_t(t_all *all)
{
	int			i;
	double		t;
	t_vector	p_local, n_local;

	i = -1;
	while (++i < all.checkrt.sp)
	{
		t = 0;
		p_local = create_vec(0, 0, 0);
		n_local = create_vec(0, 0, 0);
		if (intersection_sp(all.camera.cam, all.direction, all.sphere[i], &p_local, &n_local, &t) == 1)
		{
			all.nearest[0] = 's';
			all.nearest[1] = 'p';
			all.nearest[2] = i + 48;		// nearest sphere/point [i]
			printf("nearest = %s\n", all.nearest);
			if (t < all->closest.t_min)
			{
				all->closest.t_min = t;
				P = p_local;
				N = n_local;
			}
		}
	}
	//	while (planes)
	//	while (cylinders)

}
