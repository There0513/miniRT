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

// int		visibility()
// {
// 	return ();
// }

void light_sp(t_all *all)   // == sphere_light
{
    t_vector tmp = add_min_operation('-', all->light.point_l, all->closest.p_local);
    normalize(&tmp); // v_light = tmp
    // double	is_visible = visibility();
    // double  is_visible = 1;
    
    // double dotdot = dot(tmp, all->closest.n_local);
    // if (dotdot < 0)	// -> in the 'shadow'/darkside		is visible?! function
    //   return (1);
    // for getNorm2:
    //       all->light.bright_l += all->light.bright_l * dotdot / (sqrt(getNorm2(&all->closest.n_local)) * sqrt(getNorm2(&tmp)));
    t_vector next = add_min_operation('-', all->light.point_l, all->closest.p_local);
    all->closest.intensity = all->light.bright_l * dot(tmp, all->closest.n_local) / getNorm2(&next) * 10000;
    printf("intensity = %f\n", all->closest.intensity);
    // shadow
    
}

void apply_light(t_all *all)
{
    if (all->nearest[0] == 's' && all->nearest[1] == 'p')
        light_sp(all);
    // if (all->nearest[0] == 'p' && all->nearest[1] == 'l')
    // if (all->nearest[0] == 'c' && all->nearest[1] == 'y')
}