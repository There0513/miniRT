/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:48:06 by threiss           #+#    #+#             */
/*   Updated: 2021/08/27 17:53:07 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		visibility(t_all *all)    // 1 or 0
{

	return (1);
}

void light_sp(t_all *all)
{
    t_vector tmp = add_min_operation('-', all->light.point_l, all->closest.p_local);
    normalize(&tmp); // v_light = tmp
    double	is_visible = visibility(all);
    // double  is_visible = 0;
    
    // double dotdot = dot(tmp, all->closest.n_local);
    // if (dotdot < 0)	// -> in the 'shadow'/darkside		is visible?! function
    //     {
    //         all->closest.intensity = 0;
    //         return ;
    //     }
    // for getNorm2:
    //       all->light.bright_l += all->light.bright_l * dotdot / (sqrt(getNorm2(&all->closest.n_local)) * sqrt(getNorm2(&tmp)));
    t_vector next = add_min_operation('-', all->light.point_l, all->closest.p_local);
    all->closest.intensity = all->light.bright_l * dot(all->closest.n_local, tmp) * is_visible /
        pow(sqrt(getNorm2(&next)) / 100, 2);
    // all->closest.intensity = all->light.bright_l * dot(tmp, all->closest.n_local) / getNorm2(&next) * 10000;
    // // printf("intensity = %f\n", all->closest.intensity);
    // if (all->closest.intensity == 0)
    //________________     all->closest.intensity = 1;
}

void apply_light(t_all *all)
{
    if (all->nearest[0] == 's' && all->nearest[1] == 'p')
        light_sp(all);
    // if (all->nearest[0] == 'p' && all->nearest[1] == 'l')
    // if (all->nearest[0] == 'c' && all->nearest[1] == 'y')
}