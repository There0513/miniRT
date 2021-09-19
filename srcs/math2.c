/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:07:16 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 18:11:41 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	get_norm(t_vector *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

/*
**	sqrt(get_norm(vec)) = magnitude (length) of vector
*/

void	normalize(t_vector *vec)
{
	double	norm;

	norm = sqrt(get_norm(vec));
	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

t_vector	get_normalized(t_vector a)
{
	normalize(&a);
	return (a);
}

t_vector	create_vec(double x, double y, double z)
{
	t_vector	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}
