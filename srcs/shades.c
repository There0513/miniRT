/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:12:16 by threiss           #+#    #+#             */
/*   Updated: 2021/09/07 15:12:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int shadow_sp(t_all *all, t_sphere sphere, t_vector P, t_vector dir)
{
    t_vector PC; // hitPoint - center

	PC = add_min_operation('-', P, sphere.center);
	double a = dot(dir, dir);
	double b = 2 * dot(dir, PC);
	double c = pow(sqrt(dot(PC, PC)), 2) - sphere.radius * sphere.radius;
	double delta = b * b - (4 * a * c);
	if (delta < 0)
		return (-1);
	double t1 = (-b - sqrt(delta)) / (2.0 * a);
	double t2 = (-b + sqrt(delta)) / (2.0 * a);
    if (t1 >= 0)
    {
        all->t_visib = t1;
        return (1);
    }
    if (t2 >= 0)
    {
        all->t_visib = t2;
        return (1);
    }
    return (0);
}