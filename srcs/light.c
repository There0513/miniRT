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

int visibility(t_all *all, t_vector P, t_vector N) // return 1 or 0
{
    int i;
    t_vector dir;
    t_vector P2;
    double a, b;

    // printf("N = %f %f %f\n", N.x, N.y, N.z);
    P = add_min_operation('+', P, mult_operation('*', 0.0001, N));
    dir = get_normalized(add_min_operation('-', all->light.point_l, P));
    // printf("P = %f %f %f\tdir = %f %f %f\n", P.x, P.y, P.z, dir.x, dir.y, dir.z);
    // check each obj:
    i = -1;
    while (++i < all->checkrt.sp)
    {
        if (shadow_sp(all, all->sphere[i], P, dir) == 1)
        {
            if (i == (all->nearest[2] - 48))
                return (1);
            P2 = add_min_operation('+', P, mult_operation('*', all->t_visib, dir));
            t_vector light_p = add_min_operation('-', all->light.point_l, P);
            t_vector p2_p = add_min_operation('-', P2, P);
            a = sqrt(getNorm2(&light_p));
            b = sqrt(getNorm2(&p2_p));
            if (b < a)
                return (0);
        }
    }
    i = -1;
    while (++i < all->checkrt.cy)
    {
        if (shadow_cy(all, all->cylinder[i], P, dir) == 1)
        {
            P2 = add_min_operation('+', P, mult_operation('*', all->t_visib, dir));
            t_vector light_p = add_min_operation('-', all->light.point_l, P);
            t_vector p2_p = add_min_operation('-', P2, P);
            a = sqrt(getNorm2(&light_p));
            b = sqrt(getNorm2(&p2_p));
            if (b < a)
                return (0);
        }
    }
    i = -1;
    while (++i < all->checkrt.pl)
    {
        if (shadow_pl(all, all->plane[i], P, dir) == 1)
        {
            P2 = add_min_operation('+', P, mult_operation('*', all->t_visib, dir));
            t_vector light_p = add_min_operation('-', all->light.point_l, P);
            t_vector p2_p = add_min_operation('-', P2, P);
            a = sqrt(getNorm2(&light_p));
            b = sqrt(getNorm2(&p2_p));
            if (b < a)
                return (0);
        }
    }
    return (1);
}

void light(t_all *all, t_vector P, t_vector N)
{
    t_vector PtoLight;
    // printf("light closest.p_local = %f %f %f\n", P.x, P.y, P.z);
    // if (all->nearest[0] == 'p' && all->nearest[1] == 'l')
    //     PtoLight = add_min_operation('-', mult_operation('*', 1, all->light.point_l), P); // ?! useless
    // else
    PtoLight = add_min_operation('-', all->light.point_l, P);
    normalize(&PtoLight); // v_light
    double is_visible = visibility(all, P, N);
    // double dotdot = dot(PtoLight, N);
    // if (dotdot < 0)	// -> in the 'shadow'/darkside		is visible?! function
    //     {
    //         all->closest.intensity = 0;
    //         return ;
    //     }
    // for getNorm2:
    //       all->light.bright_l += all->light.bright_l * dotdot / (sqrt(getNorm2(&N)) * sqrt(getNorm2(&PtoLight)));
    t_vector next = add_min_operation('-', all->light.point_l, P);
    all->closest.intensity = all->light.bright_l * dot(N, PtoLight) * is_visible /
                             pow(sqrt(getNorm2(&next)) / 100, 2);
    // all->closest.intensity = all->light.bright_l * dot(PtoLight, N) / getNorm2(&next) * 10000;
    if (all->closest.intensity == 0.00)
        all->closest.intensity = 0;
    if (all->closest.intensity == 0)
        all->closest.intensity = 1;
}

// void    light_cy(t_all *all)
// {
// }

// void apply_light(t_all *all)
// {
// if (all->nearest[0] == 's' && all->nearest[1] == 'p')
// light(all);
// if (all->nearest[0] == 'c' && all->nearest[1] == 'y')
// light_cy(all);
// if (all->nearest[0] == 'p' && all->nearest[1] == 'l')
// }