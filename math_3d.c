/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:20:37 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/04 20:34:48 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		add(t_vector a, t_vector b)
{
	t_vector	add;

	add.x = a.x + b.x;
	add.y = a.y + b.y;
	add.z = a.z + b.z;
	return (add);
}

t_vector		sub(t_vector a, t_vector b)
{
	t_vector	sub;

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;
	return (sub);
}

t_vector		cross(t_vector a, t_vector b)
{
	t_vector	prod;

	prod.x = a.y * b.z - a.z * b.y;
	prod.y = a.z * b.x - a.x * b.z;
	prod.z = a.x * b.y - a.y * b.x;
	return (prod);
}

double			dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector		mult(double t, t_vector v)
{
	return (vector_init(t * v.x, t * v.y, t * v.z));
}

t_vector		normalize(t_vector v)
{
	double		length;

	length = sqrt(dot(v, v));
	if (length)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}