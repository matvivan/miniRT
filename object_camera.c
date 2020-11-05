/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:55:13 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/05 11:14:12 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		vector_matrix_prod(t_vector ray, t_matrix m)
{
	t_vector	new;

	new.x = (ray.x * m.rg.x) + (ray.y * m.up.x) + (ray.z * m.fw.x);
	new.y = (ray.x * m.rg.y) + (ray.y * m.up.y) + (ray.z * m.fw.y);
	new.z = (ray.x * m.rg.z) + (ray.y * m.up.z) + (ray.z * m.fw.z);
	return (new);
}

t_vector		get_ray(t_camera *cam, int i, int j)
{
	t_vector	ray;
	t_matrix	m;

	ray.x = cam->w / 2 - j;
	ray.y = cam->h / 2 - i;
	ray.z = (cam->w / 2) / tan(cam->fov / 2 * M_PI / 180);
	m.fw = normalize(cam->direct);
	m.rg = cross(vector_init(0, 1, 0), m.fw);
	m.up = cross(m.fw, m.rg);
	return (normalize(vector_matrix_prod(ray, m)));
}

t_matrix		matrix_init(t_camera *cam)
{
	t_matrix	m;

	m.fw = normalize(cam->direct);
	m.rg = cross(vector_init(0, 1, 0), m.fw);
	m.up = cross(m.fw, m.rg);
	return (m);
}

uint32_t		color_ratio(uint32_t color, double ratio)
{
	uint32_t   new;

	new =  (0xFF0000 & (uint32_t)((color & 0xFF0000) * ratio));
	new += (0x00FF00 & (uint32_t)((color & 0x00FF00) * ratio));
	new += (0x0000FF & (uint32_t)((color & 0x0000FF) * ratio));
	return (new);
}

double			lambert(t_point hit, t_obj *obj, t_light *light)
{
	t_vector	l;
	t_vector	n;
	double		coef;

	n = normalize(sub(hit, obj->c));
	l = normalize(sub(light->c, hit));
	coef = dot(n, l);
	if (coef < 0)
		return (0);
	return (coef);
}

double			highlight(t_vector e, t_vector l, t_vector n)
{
	t_vector	r;

	e = normalize(mult(-1, e));
	r = normalize(sub(mult(2 * dot(n, l), n), l));
	if (dot(r, e) <= 0.9)
		return (0);
	return (pow(dot(r, e), 99));
}

double			illumi(t_mlx *ptr, t_vector ray, t_obj *obj)
{
	int			k;
	int			l;
	t_vector	l_vec;
	double		illum;
	uint32_t	color;

	color = 0;
	l = 1; //no ambient
	while (ptr->light[l])
	{
		t_vector P = add(ptr->cam->origin, ray);
		t_vector n = normalize(sub(P, obj->c));

		l_vec = normalize(sub(ptr->light[l]->c, P));
		k = -1;
		while (ptr->obj[++k])
			if (ptr->obj[k]->intersect(P, l_vec, ptr->obj[k]) > 0.0001)
				break ;
		if (ptr->obj[k] == NULL)
			illum = ptr->light[l]->ratio * (lambert(P, obj, ptr->light[l]) + highlight(ray, l_vec, n));
		color += color_ratio(ptr->light[l]->argb, illum);
		++l;
	}
	if (illum > 1)
		illum = 1;
	color += color_ratio(obj->argb, 0.1);
	color += color_ratio(ptr->light[0]->argb, ptr->light[0]->ratio);
	return (color);
}

void			set_camera(t_mlx *ptr, t_camera *c, t_obj **obj)
{
	int			i;
	int			j;
	int			k;
	double		t;
	t_vector	ray;

	i = -1;
	while (++i < c->h && (j = -1))
		while (++j < c->w && (k = -1))
		{
			c->depth[i * c->w + j] = INFINITY;
			ray = get_ray(c, i, j);
			while (obj[++k])
			{
				t = obj[k]->intersect(c->origin, ray, obj[k]);
				if (0 < t && t < c->depth[i * c->w + j])
				{
					c->depth[i * c->w + j] = t;
					c->canvas[i * c->w + j] = illumi(ptr, mult(t, ray), obj[k]);
				}
			}
		}
	mlx_put_image_to_window(ptr->mlx, ptr->win, c->img_ptr, 0, 0);
}