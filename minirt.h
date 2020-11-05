/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 19:13:15 by matvivan          #+#    #+#             */
/*   Updated: 2020/11/04 20:52:35 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "math_3d.h"

typedef struct	s_matrix
{
	t_vector	rg;
	t_vector	up;
	t_vector	fw;
}				t_matrix;

typedef struct	s_camera
{
	uint32_t	**img_ptr;
	uint32_t	*canvas;
	double		*depth;
	int			w;
	int			h;
	t_point		origin;
	t_vector	direct;
	int			fov;
}				t_camera;

typedef struct	s_obj_virtual_class
{
	double		(*intersect)();
	uint32_t	argb;
	t_point		c;
	double		r;
}				t_obj;

typedef struct	s_sp
{
	double		(*intersect)();
	uint32_t	argb;
	t_point		c;
	double		r;
}				t_sp;

typedef struct	s_light
{
	uint32_t	argb;
	t_point		c;
	double		ratio;
}				t_light;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	t_camera	*cam;
	t_camera	**cam_array;
	t_obj		**obj;
	t_light		**light;
}				t_mlx;

t_point			point_init(double x, double y, double z);
t_vector		vector_init(double x, double y, double z);
t_sp			*sphere_init(t_point c, double r, uint32_t argb);
void			set_camera(t_mlx *ptr, t_camera *c, t_obj **o);
t_vector		vector_matrix_prod(t_vector ray, t_matrix m);
t_matrix		matrix_init(t_camera *cam);
double			intersect(t_vector orig, t_vector ray, t_sp *sp);
void			save_bmp(t_mlx *ptr);
void			print_stat(t_mlx *ptr, t_vector ray);

#endif
