/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:46:56 by threiss           #+#    #+#             */
/*   Updated: 2021/09/18 18:10:59 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_vector	calc_op(char sign, t_vector a, t_vector b)
{
	t_vector	new_vector;

	new_vector.x = 0;
	new_vector.y = 0;
	new_vector.z = 0;
	if (sign == '+')
	{
		new_vector.x = a.x + b.x;
		new_vector.y = a.y + b.y;
		new_vector.z = a.z + b.z;
	}
	else if (sign == '-')
	{
		new_vector.x = a.x - b.x;
		new_vector.y = a.y - b.y;
		new_vector.z = a.z - b.z;
	}
	return (new_vector);
}

t_vector	mult_op(char sign, double nbr, t_vector a)
{
	t_vector	new_vector;

	new_vector.x = 0;
	new_vector.y = 0;
	new_vector.z = 0;
	if (sign == '*')
	{
		new_vector.x = nbr * a.x;
		new_vector.y = nbr * a.y;
		new_vector.z = nbr * a.z;
	}
	return (new_vector);
}

t_vector	cross_prod(t_vector a, t_vector b)
{
	t_vector	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}
