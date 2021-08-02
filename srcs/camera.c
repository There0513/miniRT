/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:55:50 by threiss           #+#    #+#             */
/*   Updated: 2021/05/17 17:17:43 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PSEUDOCODE

Vec3	crossProduct(Vec3 a, Vec3 b)
{
	Vec3 cross;

	cross->x = a->y * b->z - a->z * b->y;
	cross->y = a->z * b->x - a->x * b->z;
	cross->z = a->x * b->y - a->y * b->x;
	return (cross);
}

matrix	lookAt(Vec3 from, Vec3 to)
{
	matrix	camtoworld;
	Vec3	forward = normalize(from - to); // orientation/direction
	Vec3	tmp(0, 1, 0);
	Vec3	right = crossProduct(normalize(tmp), forward);
	Vec3	up = crossProduct(forward, right);
	
	camtoworld[0][0] = right.x;
	camtoworld[0][1] = up.x;		// or right.y
	camtoworld[0][2] = forward.x; // or right.z

	// ...camtoworld[3][2]...etc

	return (camtoworld);
}
