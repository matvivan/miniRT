/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:45:12 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/04 21:04:02 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minirt.h"

double			nearest_pos_root(double a, double b, double c)
{
	double		disc;
	double		q;
	double		x1;
	double		x2;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	if (b > 0)
		q = -0.5 * (b + sqrt(disc));
	else
		q = -0.5 * (b - sqrt(disc));
	x1 = q / a;
	x2 = c / q;
	if (x1 > 0 && x2 > 0)
		return (x1 < x2 ? x1 : x2);
	if (x1 < 0 && x2 < 0)
		return (0);
	return (x1 > x2 ? x1 : x2);
}

double			intersect_sphere(t_vector orig, t_vector ray, t_sp *sp)
{
	t_vector	dist;
	double		b;
	double		c;

	dist = sub(orig, sp->c);
	b = 2 * dot(ray, dist);
	c = dot(dist, dist) - sp->r * sp->r;
	return (nearest_pos_root(1, b, c));
}

t_sp			*sphere_init(t_point c, double r, uint32_t argb)
{
	t_sp		*sphere;

	sphere = (t_sp *)malloc(sizeof(t_sp));
	sphere->c = c;
	sphere->r = r;
	sphere->argb = argb;
	sphere->intersect = &intersect_sphere;
	return (sphere);
}